user_query = "html body#chat-body div#container div#main div#sidebar div#sidebar-content div#widgets div.sidebar-widget ul#present-users.collapsible li div.avatar img";
var users = jQuery.makeArray($(user_query)).map(
    function(i) {
        return i.title.replace(" ", "");
    }
);

users;

textbox_query = "html body#chat-body div#container div#main div#input-area table#input-table tbody tr td.chat-input div#bubble textarea#input";
tb = $(textbox_query)[0];
tb.onkeyup = function() {
    tb.value = tb.value.replace("@all", "@" + users.join(" "));
};