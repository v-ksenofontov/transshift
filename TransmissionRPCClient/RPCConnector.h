//
//  RPCConnector.h
//  TransmissionRPCClient
//
//  Main transmission RPC connector
//

#import <Foundation/Foundation.h>
#import "RPCServerConfig.h"
#import "TRInfos.h"
#import "TRPeerInfo.h"
#import "TRFileInfo.h"
#import "TRSessionInfo.h"
#import "TrackerStat.h"

@class RPCConnector;

@protocol RPCConnectorDelegate <NSObject>

@optional - (void)connector:(RPCConnector *)cn complitedRequestName:(NSString*)requestName withError:(NSString*)errorMessage;
@optional - (void)gotAllTorrents:(TRInfos *)trInfos;
@optional - (void)gotTorrentDetailedInfo:(TRInfo*)torrentInfo;
@optional - (void)gotTorrentStopedWithId:(int)torrentId;
@optional - (void)gotTorrentResumedWithId:(int)torrentId;
@optional - (void)gotTorrentDeletedWithId:(int)torrentId;
@optional - (void)gotTorrentVerifyedWithId:(int)torrentId;
@optional - (void)gotTorrentReannouncedWithId:(int)torrentId;
@optional - (void)gotTorrentAdded;
@optional - (void)gotTorrentAddedWithMagnet:(NSString*)magnet;
@optional - (void)gotAllPeers:(NSArray*)peerInfos withPeerStat:(TRPeerStat*)stat forTorrentWithId:(int)torrentId;
@optional - (void)gotAllFiles:(NSArray*)fileInfos forTorrentWithId:(int)torrentId;
@optional - (void)gotSessionWithInfo:(TRSessionInfo*)info;
@optional - (void)gotSessionSetWithInfo:(TRSessionInfo*)info;
@optional - (void)gotFreeSpaceString:(NSString*)freeSpace;
@optional - (void)gotPortTestedWithSuccess:(BOOL)portIsOpen;
@optional - (void)gotAllTrackers:(NSArray*)trackerStats forTorrentWithId:(int)torrentId;
@optional - (void)gotTrackerRemoved:(int)trackerId forTorrentWithId:(int)torrentId;
@optional - (void)gotSetSettingsForTorrentWithId:(int)torrentId;
@optional - (void)gotAllTorrentsStopped;
@optional - (void)gotAlltorrentsResumed;
@optional - (void)gotToggledAltLimitMode:(BOOL)altLimitEnabled;

@end


@interface RPCConnector : NSObject

@property(nonatomic) NSString *lastErrorMessage;

- (instancetype)initWithConfig:(RPCServerConfig*)config andDelegate:(id<RPCConnectorDelegate>)delegate;

// make request and get all torrents
- (void)getAllTorrents;
- (void)getDetailedInfoForTorrentWithId:(int)torrentId;
- (void)stopRequests;
- (void)toggleAltLimitMode:(BOOL)altLimitsEnabled;

- (void)stopTorrent:(int)torrentId;
- (void)stopAllTorrents;
- (void)resumeTorrent:(int)torrentId;
- (void)resumeAllTorrents;
- (void)verifyTorrent:(int)torrentId;
- (void)reannounceTorrent:(int)torrentId;
- (void)deleteTorrentWithId:(int)torrentId deleteWithData:(BOOL)deleteWithData;

- (void)addTorrentWithData:(NSData*)data priority:(int)priority startImmidiately:(BOOL)startImmidiately;
- (void)addTorrentWithData:(NSData *)data priority:(int)priority startImmidiately:(BOOL)startImmidiately indexesUnwanted:(NSArray*)idxUnwanted;

- (void)addTorrentWithMagnet:(NSString*)magnetURLString priority:(int)priority startImmidiately:(BOOL)startImmidiately;

- (void)getAllPeersForTorrentWithId:(int)torrentId;
- (void)getAllFilesForTorrentWithId:(int)torrentId;

- (void)getAllTrackersForTorrentWithId:(int)torrentId;
- (void)removeTracker:(int)trackerId forTorrent:(int)torrentId;

- (void)stopDownloadingFilesWithIndexes:(NSArray*)indexes forTorrentWithId:(int)torrentId;
- (void)resumeDownloadingFilesWithIndexes:(NSArray*)indexes forTorrentWithId:(int)torrentId;
- (void)setPriority:(int)priority forFilesWithIndexes:(NSArray*)indexes forTorrentWithId:(int)torrentId;
- (void)setSettings:(TRInfo*)setttnigs forTorrentWithId:(int)torrentId;

- (void)getSessionInfo;
- (void)setSessionWithSessionInfo:(TRSessionInfo*)info;
- (void)getFreeSpaceWithDownloadDir:(NSString*)downloadDir;
- (void)portTest;

- (void)limitUploadRateWithSpeed:(int)rateKbs;
- (void)limitDownloadRateWithSpeed:(int)rateKbs;

@end


