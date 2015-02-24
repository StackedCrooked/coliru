
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Frameset//EN">
<html>
<head>
    <title>Coliru</title>
    <script type="text/javascript">

      var _gaq = _gaq || [];
      _gaq.push(['_setAccount', 'UA-37220775-1']);
      _gaq.push(['_trackPageview']);

      (function() {
        var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
        ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
        var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
      })();


    </script>
</head>
<script type="text/javascript" language="javascript">

    var app = { };
    app.elements = {};

    app.samples = {
        "Default": "#include <iostream>\n#include <string>\n#include <vector>\n\n\nusing Sentence = std::vector<std::string>;\n\n\nstd::ostream& operator<<(std::ostream& os, const Sentence & sentence)\n{\n    for (const auto & word : sentence)\n    {\n        os << word << \" \";\n    }\n    return os;\n}\n\n\nint main()\n{\n    Sentence sentence = { \"Hello\", \"from\", \"GCC\", __VERSION__, \"!\" };    \n    std::cout << sentence << std::endl;\n}\n"
    };

    document.write('<frameset rows="100%, 200" border="4" >');
    document.write(' <frame src="frame-top.html" name="top" scrolling="no" frameborder="1" />');
    document.write(' <frame src="frame-bottom.html" name="bottom" scrolling="no" frameborder="1" />');
    document.write('</frameset>');


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

        var sourceCode = localStorage.getItem("src");
        app.elements.editor.getSession().setValue(localStorage.getItem("src") || app.samples["Default"]);
        app.elements.editor.commands.bindKeys({"ctrl-l":null}) 
        app.elements.editor.commands.bindKeys({"ctrl-t":null}) 
        app.elements.editor.commands.bindKeys({"Command-l":null}) 
        app.elements.editor.commands.addCommand({
            name: 'Build and run',
                bindKey: {win: 'Ctrl-B',  mac: 'Command-B'},
                    exec: function(editor) { 
                        app.compileNow();
                    },
                    readOnly: true // false if this command should not apply in readOnly mode
                    });
        app.elements.cmd.value = localStorage.getItem("cmd") || "g++-4.8 -std=c++11 -O2 -Wall -pedantic -pthread main.cpp && ./a.out";

        app.enableUI = function(value) {
            app.elements.compileButton.disabled = !value;
            app.elements.postButton.disabled = !value;
            app.elements.editor.setReadOnly(!value);
            app.elements.editor.setReadOnly(!value);
            app.elements.cmd.disabled = !value;
            var colors = [ '#ffff00' ];
            if (parent.app.elements.fade_count === undefined)
                parent.app.elements.fade_count = 0;//Math.round(Math.random() * 10) % colors.length;

            if (!value) {
                var n = parent.app.elements.fade_count++ % colors.length;
                document.getElementsByTagName('frame')[0].contentDocument.getElementById('editor').style.zIndex = 0;
                document.getElementsByTagName('frame')[0].contentDocument.getElementById('fade').style.zIndex = 1;

                app.elements.fade.style.backgroundColor = colors[n]
                //app.elements.fade.style.backgroundImage = 'url(/random_image)';
            }
            else {
                app.elements.fade.style.backgroundColor = '#ffffff';
                //app.elements.fade.style.backgroundImage = 'none';
                document.getElementsByTagName('frame')[0].contentDocument.getElementById('editor').style.zIndex = 1;
                document.getElementsByTagName('frame')[0].contentDocument.getElementById('fade').style.zIndex = 0;
            }
            app.elements.fade.style.opacity = value ? "1.00" : "0.20";
        };
        app.enableUI(true);

        app.send = function (location, f) {
            app.enableUI(false);
            localStorage.setItem("src", app.elements.editor.getValue());
            localStorage.setItem("cmd", app.elements.cmd.value);
            var httpRequest = new XMLHttpRequest();
            httpRequest.open("POST", "http://" + window.location.hostname + ":" + window.location.port + '/' + location, true);
            httpRequest.onreadystatechange = function () {
                if (httpRequest.readyState == 4) {
                    if (httpRequest.status == 200) {
                        app.enableUI(true);
                        app.lastResult = httpRequest.responseText.trim();
                        f({src: app.elements.editor.getValue(), cmd: app.elements.cmd.value, output: app.lastResult});
                    }
                }
            };
            var post_data = JSON.stringify({
                "cmd" : app.elements.cmd.value,
                "src" : app.elements.editor.getValue()
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
                var lines = obj.output.split(/\n/);
                
                var pre_open = "<pre class='f0' onclick='window.jumpToError(this)' onmouseover='window.highlightError(this, true)' onmouseout='window.highlightError(this, false)' style='margin:0; padding:0; '>";
                var pre_close = "</pre>";
                var text = "";
                var new_line = true;
                for (var i = 0; i !== lines.length; ++i) {
                    var line = lines[i];
                    if (line !== '') {
                        text += pre_open + line.replace(/</g, '&lt').replace(/>/g, '&gt') + pre_close;
                    } else {
                        text += '<br/>';
                    }
                }
                app.elements.output.innerHTML = text;

                app.elements.cmd.value = obj.cmd;
                window.setTimeout(function() {
                    var ace_lines = app.editorDocument.getElementsByClassName("ace_line");
                    var i;
                    for (i = 0; i !== ace_lines.length; ++i) {
                        ace_lines[i].style.color = "inherit";
                    }
                    var output_lines = app.elements.output.textContent.split(/\n/);
                    for (i = 0; i != output_lines.length; ++i) {
                        try {
                            var line = output_lines[i];
                            if (line.search(/^main.cpp:\d+:\d+/) !== -1) {
                                var lineno = parseInt(line.split(":")[1]);
                                ace_lines[lineno - 1].style.color = "red";
                            }
                        }
                        catch (e) {
                            console.log(JSON.stringify(e));
                        }
                    }
                }, 100);
            });
        };

        app.postSample = function () {
            app.send("share", function (obj) {
                var url = window.location + "view?id=" + obj.output;
                window.open(url, '_self');
            });
        };

        app.previousValue = "";
    };
</script>
</html>