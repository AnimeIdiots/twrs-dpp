#include <dpp/dpp.h>
#include <dpp/fmt/format.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <toml.hpp>

std::string    BOT_TOKEN;
dpp::snowflake GUILD_ID;
dpp::snowflake ROLE_ID;
std::vector<dpp::snowflake> ACCESS_ROLE_IDS;

bool read_config()
{
    auto data = toml::parse("conf.toml");
    BOT_TOKEN = toml::find<std::string>(data, "token");
    GUILD_ID = toml::find<uint64_t>(data, "guild-id");
    ROLE_ID = toml::find<uint64_t>(data, "role-id");
    ACCESS_ROLE_IDS = toml::find<std::vector<uint64_t>>(data, "access-roles");
}

int main()
{
    if (read_config())
    {
        printf("Error reading values\n");
        return -1;
    }
    dpp::cluster bot(BOT_TOKEN, dpp::i_all_intents);

    bot.on_interaction_create([&bot](const dpp::interaction_create_t& event) {
        int check = 0;
        if (event.command.get_command_name() == "give_access") {
            std::vector<dpp::snowflake> SelfRoles = event.command.member.roles;
            for (auto id : ACCESS_ROLE_IDS)
                if (std::find(SelfRoles.begin(), SelfRoles.end(), id) != SelfRoles.end())
                    check++;
            if (!check)
            {
                event.reply(dpp::message("You don't have access to this command!").set_flags(dpp::m_ephemeral));
                return;
            }
            dpp::snowflake userR = std::get<dpp::snowflake>(event.get_parameter("user"));
            std::vector<dpp::snowflake> roles = dpp::find_guild_member(GUILD_ID, userR).roles;

            if (std::find(roles.begin(), roles.end(), ROLE_ID) == roles.end())
            {
                bot.guild_member_add_role(GUILD_ID, userR, ROLE_ID);
                event.reply(dpp::message("Done!").set_flags(dpp::m_ephemeral));
                printf("[ACCESS] '%s#%u' gave full server access to '%s#%u'\n", event.command.usr.username.c_str(), event.command.usr.discriminator, dpp::find_user(userR)->username.c_str(), dpp::find_user(userR)->discriminator);
            }
            else
            {
                event.reply(dpp::message("He already have access!").set_flags(dpp::m_ephemeral));
            }
        }
    });
 
    bot.on_ready([&bot](const dpp::ready_t& event) {
        dpp::slashcommand_map guildCMDs = bot.guild_commands_get_sync(GUILD_ID);
        for (auto const& tuple : guildCMDs)
            bot.guild_command_delete(tuple.first, GUILD_ID);
        dpp::slashcommand_map globalCMDs = bot.global_commands_get_sync();
        for (auto const& tuple : globalCMDs)
            bot.guild_command_delete(tuple.first, GUILD_ID);
        bot.guild_command_create(
            dpp::slashcommand("give_access", "Give full access to server", bot.me.id).
            add_option(dpp::command_option(dpp::co_user, "user", "User to give access to", true)),
            GUILD_ID);
        printf("  _____          _     _                  ____        _          \n |_   _|_      _(_)___| |_ ___ _ __ ___  | __ )  ___ | |_        \n   | | \\ \\ /\\ / / / __| __/ _ \\ '__/ __| |  _ \\ / _ \\| __|       \n   | |  \\ V  V /| \\__ \\ ||  __/ |  \\__ \\ | |_) | (_) | |_        \n  _|_|   \\_/\\_/ |_|___/\\__\\___|_|  |___/ |____/ \\___/ \\__| _  __ \n | |__  _   _     / \\   _ __ (_)_ __ ___   ___   _ __   __| |/ _|\n | '_ \\| | | |   / _ \\ | '_ \\| | '_ ` _ \\ / _ \\ | '_ \\ / _` | |_ \n | |_) | |_| |  / ___ \\| | | | | | | | | |  __/_| |_) | (_| |  _|\n |_.__/ \\__, | /_/   \\_\\_| |_|_|_| |_| |_|\\___(_) .__/ \\__,_|_|  \n        |___/                                   |_|              \n");
        printf("Logged in as '%s#%u'\n", bot.me.username.c_str(), bot.me.discriminator);
    });
 
    bot.start(false);
 
    return 0;
}