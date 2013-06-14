var app = { };
(function() {
    app.elements = {};

    app.samples = {
        "Default": "#include <iostream>\n#include <string>\n#include <vector>\n\n\nusing Words = std::vector<std::string>;\n\n\nstd::ostream& operator<<(std::ostream& os, const Words & words)\n{\n    for (const auto & word : words)\n    {\n        os << word << \" \";\n    }\n    return os;\n}\n\n\nint main()\n{\n    Words words = { \"Hello\", \"from\", \"GCC\", __VERSION__, \"!\" };    \n    std::cout << words << std::endl;\n}\n"
    };


    // Redirect www. to host domain.
    if (window.location.host.search(/^www./) === 0 || window.location.host.search(/^stacked/) === 0) {
        var host = window.location.hostname + "";
        host = host.replace(/^www./, "");
        host = host.replace(/^stacked/, "coliru.stacked");
        window.location.hostname = host;
    }

    window.onload = function () {


        String.prototype.trim = function () {
            return this.replace(/^\s+|\s+$/g, "");
        };
        /*function on_cmd_keydown(e) {
            if ((e.metaKey || e.ctrlKey) && e.keyCode == 66) {
                app.compileNow();
            } else if (e.keyCode == 13) {
                if (!e.shiftKey) {
                    app.compileNow();
                    e.stopPropagation();
                }
            }
            update_rows();
        }

        function on_cmd_keyup(e) {
            update_rows();
        }
        function update_rows() {
            var rows = app.elements.cmd.value.split(/\n/).length ;
            if (rows < 3) rows = 3;
            app.elements.cmd.rows = rows;
        }*/
        app.elements.compileButton = document.getElementById("compileButton");
        app.elements.postButton = document.getElementById("postButton");
        app.elements.cmd = document.getElementById("cmd");
        app.elements.output = document.getElementById("output");
        window.highlightError = function(node, b) {
            if (node.textContent.search(/^main.cpp:\d+:\d+/) === -1) {
                return;
            }
            //node.style.textDecoration = b ? 'underline' : '';
            node.style.fontWeight = b ? 'bold' : 'normal';
            node.style.cursor = b ? 'pointer' : 'auto';
        };

        app.editorDocument = document;
        app.elements.editor = document.getElementById('editor');
        app.elements.fade = document.getElementById("fade");
        app.elements.fade_count = 0;


        var sourceCode = localStorage.getItem("src");
        app.elements.editor.value = localStorage.getItem("src") || app.samples["Default"];
        app.elements.cmd.value = localStorage.getItem("cmd") || "g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out";

        app.resetCommand = function() {
            app.elements.cmd.value = "g++ -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out";
        };

        app.resetEditor = function() {
            app.elements.editor.value = app.samples["Default"];
        };

        app.enableUI = function(value) {
            app.elements.compileButton.disabled = !value;
            app.elements.postButton.disabled = !value;
            app.elements.editor.disabled = !value;
            //app.elements.editor.setReadOnly(!value);
            //app.elements.editor.setReadOnly(!value);
            app.elements.cmd.disabled = !value;
            var colors = [ '#ffff00' ];
            if (app.elements.fade_count === undefined)
                app.elements.fade_count = 0;//Math.round(Math.random() * 10) % colors.length;

            if (!value) {
                var n = app.elements.fade_count++ % colors.length;
                app.elements.fade.style.backgroundColor = colors[n]
                    //app.elements.fade.style.backgroundImage = 'url(/random_image)';
            }
            else {
                app.elements.fade.style.backgroundColor = '#ffffff';
                //app.elements.fade.style.backgroundImage = 'none';
            }
            app.elements.fade.style.zIndex = value ? 0 : 1;
            app.elements.fade.style.opacity = value ? "1.00" : "0.10";
        };
        app.enableUI(true);

        app.send = function (location, f) {
            app.enableUI(false);
            localStorage.setItem("src", app.elements.editor.value);
            localStorage.setItem("cmd", app.elements.cmd.value);
            var httpRequest = new XMLHttpRequest();
            httpRequest.open("POST", "http://" + window.location.hostname + ":" + window.location.port + '/' + location, true);
            httpRequest.onreadystatechange = function () {
                if (httpRequest.readyState == 4) {
                    if (httpRequest.status == 200) {
                        app.enableUI(true);
                        app.lastResult = httpRequest.responseText.trim();
                        f({src: app.elements.editor.value, cmd: app.elements.cmd.value, output: app.lastResult});
                    }
                }
            };
            var post_data = JSON.stringify({
                "cmd" : app.elements.cmd.value,
                "src" : app.elements.editor.value
            });
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
        app.compileNow = function () {
            if (app.elements.compileButton.disabled) return;
            app.send("compile", function (obj) {
                app.elements.output.value = obj.output;
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
})();
