#define PURPLE_PLUGINS

#include <glib.h>

#include "notify.h"
#include "plugin.h"
#include "server.h"
#include "version.h"

static gboolean

receiving_im_msg_cb(PurpleAccount *account, char **sender, char **buffer,
                    PurpleConversation *conv, PurpleMessageFlags *flags, void *data) {

    purple_conversation_write(conv, "", "Got message signal!", PURPLE_MESSAGE_SYSTEM | PURPLE_MESSAGE_NO_LOG, time(NULL));
}

plugin_load(PurplePlugin *plugin) {
    purple_signal_connect(
        purple_plugins_get_handle(), 
        'received-im-msg',
        plugin,
        PURPLE_CALLBACK(receiving_im_msg_cb),
        NULL
    );

    return TRUE;
}

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    NULL,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,
    "gtk-jcavanagh-pidgin_cloud_to_butt",
    "Cloud to Butt", 
    "1.0",
    "Cloud to butt.  Yep.",
    "Too many clouds?  Not enough butts?  Problem solved!",
    "Joe Cavanagh <joe@jlcavanagh.com>",
    "https://github.com/jcavanagh/pidgin-cloud-to-butt",
    plugin_load,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};                            
    
static void                        
init_plugin(PurplePlugin *plugin)
{                                  
}

PURPLE_INIT_PLUGIN(hello_world, init_plugin, info)
