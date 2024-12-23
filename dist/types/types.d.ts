/**
 * A discord result code.
 * See https://discord.com/developers/docs/game-sdk/discord#data-models-result-enum
 * for the meaning of the code.
 */
export declare enum DiscordResult {
    Ok = 0,
    ServiceUnavailable = 1,
    InvalidVersion = 2,
    LockFailed = 3,
    InternalError = 4,
    InvalidPayload = 5,
    InvalidCommand = 6,
    InvalidPermissions = 7,
    NotFetched = 8,
    NotFound = 9,
    Conflict = 10,
    InvalidSecret = 11,
    InvalidJoinSecret = 12,
    NoEligibleActivity = 13,
    InvalidInvite = 14,
    NotAuthenticated = 15,
    InvalidAccessToken = 16,
    ApplicationMismatch = 17,
    InvalidDataUrl = 18,
    InvalidBase64 = 19,
    NotFiltered = 20,
    LobbyFull = 21,
    InvalidLobbySecret = 22,
    InvalidFilename = 23,
    InvalidFileSize = 24,
    InvalidEntitlement = 25,
    NotInstalled = 26,
    NotRunning = 27,
    InsufficientBuffer = 28,
    PurchaseCanceled = 29,
    InvalidGuild = 30,
    InvalidEvent = 31,
    InvalidChannel = 32,
    InvalidOrigin = 33,
    RateLimited = 34,
    OAuth2Error = 35,
    SelectChannelTimeout = 36,
    GetGuildTimeout = 37,
    SelectVoiceForceRequired = 38,
    CaptureShortcutAlreadyListening = 39,
    UnauthorizedForAchievement = 40,
    InvalidGiftCode = 41,
    PurchaseError = 42,
    TransactionAborted = 43
}
export declare enum PremiumType {
    None = "None",
    Tier1 = "Tier1",
    Tier2 = "Tier2"
}
/**
 * A discord user's data.
 *
 * @example
 * ```js
 * {
 *   isBot: false,
 *   username: 'arthuro555',
 *   avatar: '13fc7e7e6969c3608e97c56bd86c741a',
 *   discriminator: '9738',
 *   id: 425714310262816776n,
 * }
 * ```
 */
export interface User {
    /**
     * True is the user is a bot.
     */
    isBot: boolean;
    /**
     * The username of the user.
     */
    username: string;
    /**
     * The hash of the avatar of the user.
     * You can get the avatar image from the discord cdn at
     * https://cdn.discordapp.com/avatars/${user.id}/${user.avatar}.png
     * See https://discord.com/developers/docs/reference#image-formatting
     */
    avatar: string;
    /**
     * The user discriminator, also know as tag.
     * This is the 4 digits after the # in the discord identifier.
     */
    discriminator: string;
    /**
     * The unique user ID.
     */
    id: Number;
}
/**
 * Unix timestamps of an activity.
 */
export interface ActivityTimestamps {
    start?: number;
    end?: number;
}
/**
 * Assets displayed on an activity.
 */
export interface ActivityAssets {
    largeImage?: string;
    largeText?: string;
    smallImage?: string;
    smallText?: string;
}
/**
 * Size information on a party of an activity.
 */
export interface ActivityPartySize {
    /**
     * The amount of players in the party.
     */
    currentSize?: number;
    /**
     * The maximum amount of players in the party.
     */
    maxSize?: number;
}
/**
 * A party of an activity.
 */
export interface ActivityParty {
    /**
     * The unique identifier/name of the party.
     */
    id?: string;
    /**
     * The size information of the party.
     */
    size?: ActivityPartySize;
}
/**
 * A party of an activity.
 */
export interface ReadonlyActivityParty {
    /**
     * The unique identifier/name of the party.
     */
    id: string;
    /**
     * The size information of the party.
     */
    size: Readonly<Required<ActivityPartySize>>;
}
/**
 * Secrets of an activity.
 */
export interface ActivitySecrets {
    join?: string;
    match?: string;
    spectate?: string;
}
/**
 * An activity, also known as Rich Presence data, of the current user.
 */
export interface Activity {
    /**
     * The current game state of the user.
     */
    state?: string;
    /**
     * Details on the game state of the user.
     */
    details?: string;
    /**
     * True if the user is currently in a match.
     */
    instance?: boolean;
    /**
     * Assets displayed by the activity.
     */
    assets?: ActivityAssets;
    /**
     * Start and end timestamps of the activity.
     */
    timestamps?: ActivityTimestamps;
    /**
     * Information on the party of the user.
     */
    party?: ActivityParty;
    /**
     * The secrets necessary to join the users party.
     */
    secrets?: ActivitySecrets;
}
/**
 * An activity, also known as Rich Presence payload, of another user.
 */
interface _ReadonlyActivity extends Activity {
    /**
     * The ID of the application the user is using.
     */
    appId: string;
    /**
     * The name of the application the user is using.
     */
    name: string;
    assets: Readonly<Required<ActivityAssets>>;
    timestamps: Readonly<Required<ActivityTimestamps>>;
    party: ReadonlyActivityParty;
    secrets: Readonly<Required<ActivitySecrets>>;
}
export declare type ReadonlyActivity = Readonly<Required<_ReadonlyActivity>>;
/**
 * A callback for the invite event.
 * @param type - The type of invitation.
 * @param user - The user who sent the invitation.
 * @param activity - The activity of the user who sent the invitation.
 */
export declare type InviteCallback = (type: "join" | "spectate", user: User, activity: ReadonlyActivity) => void;
/**
 * Optional settings for the {@link Discord} contructor.
 */
export interface DiscordOptions {
    /**
     * If true, require discord to be present to initialize the sdk.
     * @default false
     */
    requireDiscord?: boolean;
    /**
     * The interval in milliseconds between each
     * update with the Discord client.
     * @default 200
     */
    callbacksInterval?: number;
    /**
     * Disables the automatic setInterval for the callbacks.
     * To use if you want to integrate running callbacks in your own events loop.
     * @default false
     */
    disableInterval?: boolean;
}
export declare class UserManager {
    /**
     * Get the current user's data.
     */
    getCurrentUser(): Promise<User>;
    /**
     * Get informations on a specific user.
     * @param userId The user to get information from.
     */
    getUser(userId: Number): Promise<User>;
}
export {};
//# sourceMappingURL=types.d.ts.map