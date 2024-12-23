import EventsEmitter from "events";
import { Activity } from "..";

declare class RP extends EventsEmitter {
  updatePresence(d: Activity): void;
  reply(user, response): void;
}

declare const makeClient: (clientID: number) => void;
export = makeClient;
