$ = function(el) {
  function Proxy(obj) {
    this.el = el;
    this.keys = function() { 
      var keys = [];
      for (var key in el) keys.push(key);
      return keys;
    }
  }
  return new Proxy(el);
}



$(window).keys()

