!function(e,i){"object"==typeof exports&&"undefined"!=typeof module?i(exports,require("bindings")):"function"==typeof define&&define.amd?define(["exports","bindings"],i):i((e||self).discordGameSdk={},e.bindings)}(this,function(e,i){function n(e){return e&&"object"==typeof e&&"default"in e?e:{default:e}}const t=n(i).default("binding").DiscordNative;var l,o;e.DiscordResult=void 0,(l=e.DiscordResult||(e.DiscordResult={}))[l.Ok=0]="Ok",l[l.ServiceUnavailable=1]="ServiceUnavailable",l[l.InvalidVersion=2]="InvalidVersion",l[l.LockFailed=3]="LockFailed",l[l.InternalError=4]="InternalError",l[l.InvalidPayload=5]="InvalidPayload",l[l.InvalidCommand=6]="InvalidCommand",l[l.InvalidPermissions=7]="InvalidPermissions",l[l.NotFetched=8]="NotFetched",l[l.NotFound=9]="NotFound",l[l.Conflict=10]="Conflict",l[l.InvalidSecret=11]="InvalidSecret",l[l.InvalidJoinSecret=12]="InvalidJoinSecret",l[l.NoEligibleActivity=13]="NoEligibleActivity",l[l.InvalidInvite=14]="InvalidInvite",l[l.NotAuthenticated=15]="NotAuthenticated",l[l.InvalidAccessToken=16]="InvalidAccessToken",l[l.ApplicationMismatch=17]="ApplicationMismatch",l[l.InvalidDataUrl=18]="InvalidDataUrl",l[l.InvalidBase64=19]="InvalidBase64",l[l.NotFiltered=20]="NotFiltered",l[l.LobbyFull=21]="LobbyFull",l[l.InvalidLobbySecret=22]="InvalidLobbySecret",l[l.InvalidFilename=23]="InvalidFilename",l[l.InvalidFileSize=24]="InvalidFileSize",l[l.InvalidEntitlement=25]="InvalidEntitlement",l[l.NotInstalled=26]="NotInstalled",l[l.NotRunning=27]="NotRunning",l[l.InsufficientBuffer=28]="InsufficientBuffer",l[l.PurchaseCanceled=29]="PurchaseCanceled",l[l.InvalidGuild=30]="InvalidGuild",l[l.InvalidEvent=31]="InvalidEvent",l[l.InvalidChannel=32]="InvalidChannel",l[l.InvalidOrigin=33]="InvalidOrigin",l[l.RateLimited=34]="RateLimited",l[l.OAuth2Error=35]="OAuth2Error",l[l.SelectChannelTimeout=36]="SelectChannelTimeout",l[l.GetGuildTimeout=37]="GetGuildTimeout",l[l.SelectVoiceForceRequired=38]="SelectVoiceForceRequired",l[l.CaptureShortcutAlreadyListening=39]="CaptureShortcutAlreadyListening",l[l.UnauthorizedForAchievement=40]="UnauthorizedForAchievement",l[l.InvalidGiftCode=41]="InvalidGiftCode",l[l.PurchaseError=42]="PurchaseError",l[l.TransactionAborted=43]="TransactionAborted",e.PremiumType=void 0,(o=e.PremiumType||(e.PremiumType={})).None="None",o.Tier1="Tier1",o.Tier2="Tier2",e.Discord=class extends t{constructor(e,i){super(e,i),this.i=void 0;const{callbacksInterval:n}=i||{};this.i=setInterval(()=>{try{this.runCallbacks()}catch(e){console.error("Error while running discord callback: ",e)}},n||200)}destroy(){clearInterval(this.i)}}});
//# sourceMappingURL=discord-game-sdk.umd.js.map
