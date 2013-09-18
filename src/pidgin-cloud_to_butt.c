#define PURPLE_PLUGINS

#include <glib.h>
#include <string.h>

#include "conversation.h"
#include "notify.h"
#include "plugin.h"
#include "version.h"

char *str_replace ( const char *string, const char *substr, const char *replacement ){
    char *tok = NULL;
    char *newstr = NULL;
    char *oldstr = NULL;
    char *head = NULL;
   
    /* if either substr or replacement is NULL, duplicate string a let caller handle it */
    if ( substr == NULL || replacement == NULL ) return strdup (string);
    newstr = strdup (string);
    head = newstr;
    while ( (tok = strstr ( head, substr ))){
        oldstr = newstr;
        newstr = malloc ( strlen ( oldstr ) - strlen ( substr ) + strlen ( replacement ) + 1 );

        /*failed to alloc mem, free old string and return NULL */
        if ( newstr == NULL ){
            free (oldstr);
            return NULL;
        }

        memcpy ( newstr, oldstr, tok - oldstr );
        memcpy ( newstr + (tok - oldstr), replacement, strlen ( replacement ) );
        memcpy ( newstr + (tok - oldstr) + strlen( replacement ), tok + strlen ( substr ), strlen ( oldstr ) - strlen ( substr ) - ( tok - oldstr ) );
        memset ( newstr + strlen ( oldstr ) - strlen ( substr ) + strlen ( replacement ) , 0, 1 );
        /* move back head right after the last replacement */
        head = newstr + (tok - oldstr) + strlen( replacement );
        free (oldstr);
    }

    return newstr;
}

static gboolean receiving_im_msg_cb(PurpleAccount *account, char **sender, char **message, PurpleConversation *conv, PurpleMessageFlags *flags) {
    char *newMessage = str_replace(*message, "the cloud", "my butt");

    free(*message);
    *message = newMessage;

    purple_conversation_write(conv, "", newMessage, PURPLE_MESSAGE_SYSTEM | PURPLE_MESSAGE_NO_LOG, time(NULL));

    return FALSE;
}

static gboolean plugin_load(PurplePlugin *plugin) {
    //Connect to conversation signal
    purple_signal_connect(
        purple_conversations_get_handle(), 
        "receiving-im-msg",
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
