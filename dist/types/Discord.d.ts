import { DiscordNative } from "./native";
import { DiscordOptions } from "./types";
/**
 * The Discord Game SDK wrapper class. Initialize it with your client ID.
 * You can get a client ID from the discord developer portal:
 * https://discord.com/developers/applications
 *
 * @example Initialize a discord client
 * ```js
 * const Discord = require('discord-game-sdk');
 * const client = new Discord(461618159171141643);
 * ```
 *
 * @example Initialize a discord client that requires discord
 * ```js
 * const Discord = require('discord-game-sdk');
 * const client = new Discord(461618159171141643, { requireDiscord: true });
 * ```
 */
export declare class Discord extends DiscordNative {
    private readonly _timer;
    constructor(clientId: number, options?: DiscordOptions);
    /**
     * To be called when done with the Discord SDK.
     * Clears the callbacks timer.
     */
    destroy(): void;
}
//# sourceMappingURL=Discord.d.ts.map