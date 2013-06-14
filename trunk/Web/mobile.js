window.app = { };

var _gaq = _gaq || [];
_gaq.push(['_setAccount', 'UA-37220775-1']);
_gaq.push(['_trackPageview']);

(function () {
    var ga = document.createElement('script');
    ga.type = 'text/javascript';
    ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(ga, s);
})();


app.elements = {};

app.samples = {
    "Default":"#include <iostream>\n#include <string>\n#include <vector>\n\n\nusing Words = std::vector<std::string>;\n\n\nstd::ostream& operator<<(std::ostream& os, const Words & words)\n{\n    for (const auto & word : words)\n    {\n        os << word << \" \";\n    }\n    return os;\n}\n\n\nint main()\n{\n    Words words = { \"Hello\", \"from\", \"GCC\", __VERSION__, \"!\" };    \n    std::cout << words << std::endl;\n}\n"
};


// Redirect www. to host domain.
if (window.location.host.search(/^www./) === 0 || window.location.host.search(/^stacked/) === 0) {
    var host = window.location.hostname + "";
    host = host.replace(/^www./, "");
    host = host.replace(/^stacked/, "coliru.stacked");
    window.location.hostname = host;
}

app.on_cmd_keydown = function (e) {
    if (e.keyCode == 13) {
        if (!e.shiftKey) {
            app.compileNow();
            e.stopPropagation();
        }
    }
};


window.onload = function () {


    String.prototype.trim = function () {
        return this.replace(/^\s+|\s+$/g, "");
    };
    app.elements.compile = document.getElementById("compile");
    app.elements.postButton = document.getElementById("postButton");
    app.elements.output = document.getElementById("output");
    window.highlightError = function (node, b) {
        if (node.textContent.search(/^main.cpp:\d+:\d+/) === -1) {
            return;
        }
        //node.style.textDecoration = b ? 'underline' : '';
        node.style.fontWeight = b ? 'bold' : 'normal';
        node.style.cursor = b ? 'pointer' : 'auto';
    };

    app.editorDocument = document;
    app.elements.editor = document.getElementById("editor");
    ////app.elements.fade = document.getElementById("fade");

    app.elements.editor.value = localStorage.getItem("src") || app.samples["Default"];
    app.defaultCmd = "g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out";
    app.cmd = localStorage.getItem("cmd") || app.defaultCmd;

    app.resetEditor = function () {
        app.elements.editor.value = app.samples["Default"];
    };

    app.enableUI = function (value) {
        app.elements.compile.disabled = !value;
        app.elements.postButton.disabled = !value;
        app.elements.editor.disabled = !value;

        //app.elements.fade.style.backgroundColor = value ? '#ffffff' : '#00ff00';
        //app.elements.fade.style.zIndex = value ? 0 : 1;
        //app.elements.fade.style.opacity = value ? "1.00" : "0.40";
    };
    app.enableUI(true);

    app.send = function (location, f) {
        app.enableUI(false);
        localStorage.setItem("src", app.elements.editor.value);
        localStorage.setItem("cmd", app.cmd);
        var httpRequest = new XMLHttpRequest();
        httpRequest.open("POST", "http://" + window.location.hostname + ":" + window.location.port + '/' + location, true);
        httpRequest.onreadystatechange = function () {
            if (httpRequest.readyState == 4) {
                if (httpRequest.status == 200) {
                    app.enableUI(true);
                    app.lastResult = httpRequest.responseText.trim();
                    f({src:app.elements.editor.value, cmd: app.cmd, output:app.lastResult});
                }
            }
        };
        var post_data = JSON.stringify({
            "cmd":app.cmd,
            "src":app.elements.editor.value
        });
        console.log(post_data);
        httpRequest.send(post_data);
    };


    app.previousValue = "";

    app.feedback = function (msg) {
        if (!msg) return;
        var httpRequest = new XMLHttpRequest();
        httpRequest.open("POST", "http://" + window.location.hostname + ":" + window.location.port + '/feedback', true);
        httpRequest.onreadystatechange = function () {
            if (httpRequest.readyState == 4) {
                if (httpRequest.status == 200) {
                    window.location = "http://coliru.stacked-crooked.com/feedback";
                }
            }
        };
        httpRequest.send(msg);

    };
    app.toggleOutputWindow = function() {
        if (app.elements.output.style.display !== 'none') {
            app.elements.output.style.display = 'none';
        } else {
            app.elements.output.style.display = 'inherit';
        }
    };
    app.configureBuildCommand = function() {
        app.cmd = prompt("Build command: ", app.cmd || app.defaultCmd) || app.defaultCmd;
    };
    app.compileNow = function () {
        if (app.elements.compile.disabled) return;
        app.send("compile", function (obj) {
            app.elements.output.value = obj.output;
            app.elements.output.style.display = 'inherit';
        });
    };

    app.postSample = function () {
        app.send("share", function (obj) {
            var url = window.location.pathname = "view?id=" + obj.output;
            window.open(url, '_self');
        });
    };
    app.previousValue = "";
};
