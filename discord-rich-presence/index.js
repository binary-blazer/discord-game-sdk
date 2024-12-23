const EventEmitter = require("events");
const { Discord } = require("..");

function makeClient(clientId) {
  const client = new Discord(clientId);

  const instance = new (class RP extends EventEmitter {
    updatePresence(d) {
      client.updateActivity(d).catch((e) => this.emit("error", e));
    }

    reply(user, response) {
      const handle = (e) => this.emit("error", e);
      switch (response) {
        case "YES":
          client.sendJoinInvite(user).catch(handle);
          break;
        case "NO":
        case "IGNORE":
          client.closeJoinRequest(user).catch(handle);
          break;
        default:
          throw new RangeError("unknown response");
      }
    }

    disconnect() {
      client.destroy().catch((e) => this.emit("error", e));
    }
  })();

  client.on("join", ({ secret }) => {
    instance.emit("join", secret);
  });

  client.on("spectate", ({ secret }) => {
    instance.emit("spectate", secret);
  });

  client.on("joinRequest", (user) => {
    instance.emit("joinRequest", user);
  });

  return instance;
}

module.exports = makeClient;
