#include <iostream>
#include <dpp/dpp.h>
#include <algorithm>
#include <vector>

const std::string    BOT_TOKEN    = "NzQwNTc1MjQ2NTA3MTgwMDYy.XyrAcQ.S3cF1Z1ykw-T7x-5zZoTPwEIck8";
const dpp::snowflake GUILD_ID  =  704602626721054771;
const dpp::snowflake ROLE_ID = 961989945327779940;

int main()
{
    dpp::cluster bot(BOT_TOKEN);
 
    bot.on_interaction_create([&bot](const dpp::interaction_create_t& event) {
        if (event.command.get_command_name() == "give_access") {
        dpp::snowflake userR = std::get<dpp::snowflake>(event.get_parameter("user"));
        //if (std::find(dpp::find_guild_member(GUILD_ID, userR).roles.begin(), dpp::find_guild_member(GUILD_ID, userR).roles.end(), userR) != dpp::find_guild_member(GUILD_ID, userR).roles.end() )
        //{
            bot.guild_member_add_role(GUILD_ID, userR, ROLE_ID);
            dpp::message msg("Done!");
            msg.set_flags(dpp::m_ephemeral);
            event.reply(msg);
            //event.reply("Done!");
        //}
        //else
        //{
          //  event.reply("He already have access!");
        //}
        printf("[ACCESS] '%s#%u' gave full server access to '%s#%u'", event.command.usr.username, event.command.usr.discriminator, dpp::find_user(userR)->username, dpp::find_user(userR)->discriminator);
    }
    });
 
    bot.on_ready([&bot](const dpp::ready_t& event) {
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.guild_command_create(
                dpp::slashcommand("give_access", "Give full access to server", bot.me.id).
                    add_option(dpp::command_option(dpp::co_user, "user", "User to give access to", true)),
                GUILD_ID
            );
        }
    });
 
    bot.start(false);
 
    return 0;
}