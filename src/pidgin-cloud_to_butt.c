#define PURPLE_PLUGINS

#include <glib.h>
#include <string.h>

#include "conversation.h"
#include "notify.h"
#include "plugin.h"
#include "version.h"

char *str_replace ( const char *string, const char *substr, const char *replacement, gboolean ignore_case){
    char *tok = NULL;
    char *newstr = NULL;
    char *oldstr = NULL;
    char *head = NULL;
   
    /* if either substr or replacement is NULL, duplicate string a let caller handle it */
    if ( substr == NULL || replacement == NULL ) return strdup (string);
    newstr = strdup (string);
    head = newstr;
    do {
        if(ignore_case) {
            tok = strcasestr ( head, substr );
        } else {
            tok = strstr( head, substr );
        }

        if(!tok) {
            return newstr;
        }

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
    } while ( tok );

    return newstr;
}

static gboolean receiving_msg_cb(PurpleAccount *account, char **sender, char **message, PurpleConversation *conv, PurpleMessageFlags *flags) {
    //Naively try to match case in a few common scenarios
    //It's a shame I'm terrible at C, or else this could be way cooler and actually solve the general case
    char *newMessage = str_replace(*message, "the cloud", "my butt", FALSE);
    newMessage = str_replace(newMessage, "THE CLOUD", "MY BUTT", FALSE);
    newMessage = str_replace(newMessage, "The Cloud", "My Butt", FALSE);
    newMessage = str_replace(newMessage, "the Cloud", "my Butt", FALSE);
    newMessage = str_replace(newMessage, "The cloud", "My butt", FALSE);
    newMessage = str_replace(newMessage, "Cloud", "Butt", FALSE);

    //Replace all remaining clouds with butts, regardless of case
    newMessage = str_replace(newMessage, "cloud", "butt", TRUE);

    free(*message);
    *message = newMessage;

    return FALSE;
}

static gboolean plugin_load(PurplePlugin *plugin) {
    //Connect to conversation signals
    purple_signal_connect(
        purple_conversations_get_handle(), 
        "receiving-im-msg",
        plugin,
        PURPLE_CALLBACK(receiving_msg_cb),
        NULL
    );

    purple_signal_connect(
        purple_conversations_get_handle(), 
        "receiving-chat-msg",
        plugin,
        PURPLE_CALLBACK(receiving_msg_cb),
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
    //Nothing to do
}

PURPLE_INIT_PLUGIN("pidgin-cloud-to-butt", init_plugin, info)
