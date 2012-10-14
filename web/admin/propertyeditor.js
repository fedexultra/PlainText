
function PropertyEditor() {

    this.element = element(".property-editor");

    this.editor = null;

    this.options = {};

    this.init();
}

PropertyEditor.prototype.init = function() {

    var self = this;

    loadScript("codemirror/codemirror.js", function() {
        loadScript("codemirror/javascript.js");
        loadScript("codemirror/util/simple-hint.js");
        loadScript("codemirror/util/javascript-hint.js");

        self.editor = CodeMirror.fromTextArea(self.element.querySelector("textarea"), {
            "lineNumbers": true,
            "matchBrackets": true,
            "tabSize": 4,
            "indentUnit": 4,
            "indentWithTabs": false
        });
    });

    loadStyle("codemirror/codemirror.css");
    loadStyle("codemirror/util/simple-hint.css");

    this.attachListeners();
}

PropertyEditor.prototype.attachListeners = function() {

    var self = this;

    this.element.querySelector(".cancel-button").addEventListener("click", function() {
        self.close();
    }, false);

    this.element.querySelector(".submit-button").addEventListener("click", function() {
        self.save();
    }, false);
}

PropertyEditor.prototype.edit = function(value, options) {

    this.options = options || {};

    if (value && value.trimmed().startsWith("(function")) {
        this.editor.setOption("mode", "javascript");
        this.editor.setOption("lineWrapping", false);
    } else {
        this.editor.setOption("mode", "null");
        this.editor.setOption("lineWrapping", true);
    }
    this.editor.setValue(value !== undefined ? value.trimmed() : "");

    var submitButtonLabel = options.submitButtonLabel || "Save";
    this.element.querySelector(".submit-button").textContent = submitButtonLabel;

    this.element.show();

    this.editor.focus();
};

PropertyEditor.prototype.save = function() {

    var value = self.editor.getValue();

    if (this.options.onsave) {
        this.options.onsave(value);
    } else {
        this.close();
    }
};

PropertyEditor.prototype.close = function() {

    if (this.options.onclose) {
        this.options.onclose();
    }

    this.element.hide();
};

scriptLoaded("propertyeditor.js");
