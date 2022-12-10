class EvtEmitter{

  constructor() {
    this._events = {};
  }

  throwError(errname) {
    throw new Error(errname);
  }

  on(name, listener) {
    if (!this._events[name]) {
      this._events[name] = [];
    }
    this._events[name].push(listener);
  }

  removeListener(name, listenerToRemove) {
    if (!this._events[name]) {
      this.throwError(`Can\'t remove listener, Event ${name} doesn\'t exist.`);
    }

    this._events[name] = this._events[name].filter(listener => listener !== listenerToRemove);
  }

  emit(name, payload) {
    if (!this._events[name]) {
      this.throwError(`Can\'t emit an event. Event ${name} doesn\'t exist.`);
    }

    this._events[name].forEach(callback => {
      callback(payload); 
    })
  }
}

function main() {
  const eve = new EvtEmitter();
  let somecallb = () => {console.log("shit im ded")};
  let anothercallb = () => {console.log("shit for real")};
  eve.on("die", somecallb);
  eve.on("die", anothercallb);
  eve.emit("die");
  eve.removeListener("die", somecallb);
  eve.emit("die");
  
} main();

module.exports = EvtEmitter;
