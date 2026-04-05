var Module = Module || {};

(function () {
  var stdinQueue = [];

  function writeToTerminal(text) {
    if (typeof window !== "undefined" && typeof window.appendTerminalText === "function") {
      window.appendTerminalText(text);
    }
  }

  function enqueueLine(line) {
    var content = String(line || "");
    for (var i = 0; i < content.length; i += 1) {
      stdinQueue.push(content.charCodeAt(i));
    }
    stdinQueue.push(10);
  }

  if (typeof window !== "undefined") {
    window.consumeInputLine = enqueueLine;
  }

  Module.preRun = Module.preRun || [];
  Module.preRun.push(function () {
    FS.init(
      function stdin() {
        if (stdinQueue.length === 0) return null;
        return stdinQueue.shift();
      },
      function stdout(chr) {
        if (chr === null || chr === undefined) return;
        writeToTerminal(String.fromCharCode(chr));
      },
      function stderr(chr) {
        if (chr === null || chr === undefined) return;
        writeToTerminal(String.fromCharCode(chr));
      }
    );
  });

  Module.print = function (text) {
    writeToTerminal(String(text) + "\n");
  };

  Module.printErr = function (text) {
    writeToTerminal(String(text) + "\n");
  };

  Module.stdout = function (chr) {
    if (chr === null || chr === undefined) return;
    writeToTerminal(String.fromCharCode(chr));
  };

  Module.stderr = function (chr) {
    if (chr === null || chr === undefined) return;
    writeToTerminal(String.fromCharCode(chr));
  };
})();
