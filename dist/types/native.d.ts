import { DiscordOptions, DiscordResult, Activity, User, InviteCallback, UserManager } from "./types";
declare class Discord {
    constructor(clientId: number, options?: DiscordOptions);
    /**
     * Initializes the UserManager if necessary and returns it.
     */
    getUserManager(): UserManager;
    /**
     * Runs the pending Discord callbacks.
     * Note that this will be called automatically unless {@link DiscordOptions.disableInterval} is set to true.
     * To be called very regularly.
     */
    runCallbacks(): void;
    /**
     * Returns the current status of the Discord SDK.
     */
    getStatus(): DiscordResult;
    updateActivity(newActivity: Activity): Promise<DiscordResult>;
    /**
     * Add an events listener for a discord event.
     * @param eventType The type of event to listen to.
     * @param cb The callback for that event.
     */
    on(eventType: "userUpdate", cb: () => void): number;
    on(eventType: "joinRequest", cb: (user: User) => void): number;
    on(eventType: "join" | "spectate", cb: (secret: string) => void): number;
    on(eventType: "invite", cb: InviteCallback): number;
}
declare const DiscordNative: typeof Discord;
export { DiscordNative };
//# sourceMappingURL=native.d.ts.map