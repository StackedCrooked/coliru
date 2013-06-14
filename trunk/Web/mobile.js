
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

// Redirect www. to host domain.
if (window.location.host.search(/^www./) === 0 || window.location.host.search(/^stacked/) === 0) {
    var host = window.location.hostname + "";
    host = host.replace(/^www./, "");
    host = host.replace(/^stacked/, "coliru.stacked");
    window.location.hostname = host;
}

window.onload = function () {

    window.app = { };
    app.elements = {};

    app.samples = {
        "Default":"#include <iostream>\n#include <string>\n#include <vector>\n\n\nusing Words = std::vector<std::string>;\n\n\nstd::ostream& operator<<(std::ostream& os, const Words & words)\n{\n    for (const auto & word : words)\n    {\n        os << word << \" \";\n    }\n    return os;\n}\n\n\nint main()\n{\n    Words words = { \"Hello\", \"from\", \"GCC\", __VERSION__, \"!\" };    \n    std::cout << words << std::endl;\n}\n"
    };



    app.on_cmd_keydown = function (e) {
        if (e.keyCode == 13) {
            if (!e.shiftKey) {
                app.compileNow();
                e.stopPropagation();
            }
        }
    };

    String.prototype.trim = function () {
        return this.replace(/^\s+|\s+$/g, "");
    };
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
        console.log("app: " + app);
        console.log("app.elements: " + app.elements);
        console.log("app.elements.compileButton: " + app.elements.compileButton);
        app.elements.compileButton.disabled = !value;
        app.elements.postButton.disabled = !value;
        app.elements.editor.disabled = !value;
    };

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
        var button = document.getElementById('outputButton');
        var hidden = false;
        if (app.elements.output.style.display === 'inherit') {
            app.elements.output.style.display = 'none';
            hidden = true;
        } else {
            app.elements.output.style.display = 'inherit';
        }
        button.style.fontWeight = hidden ? 'inherit' : 'bold';
        //button.textContent = hidden ? "Show output" : "Hide output";
    };
    app.configureBuildCommand = function() {
        app.cmd = prompt("Build command: ", app.cmd || app.defaultCmd) || app.cmd || app.defaultCmd;
    };
    app.compileNow = function () {
        if (app.elements.compileButton.disabled) return;
        app.elements.compileButton.fontWeight = 'bold';
        app.send("compile", function (obj) {
            app.elements.compileButton.fontWeight = 'inherit';
            app.elements.output.value = obj.output;
            app.toggleOutputWindow(); // toggle in any case
            if (app.elements.output.style.display === 'none') {
                app.toggleOutputWindow(); // undo the toggle if needed
            }
        });
    };

    app.postSample = function () {
        app.send("share", function (obj) {
            var url = window.location.pathname = "view?id=" + obj.output;
            window.open(url, '_self');
        });
    };
    app.previousValue = "";

    app.elements.compileButton = document.getElementById("compileButton");
    app.elements.postButton = document.getElementById("postButton");
    app.elements.output = document.getElementById("output");
    app.enableUI(true);
};
