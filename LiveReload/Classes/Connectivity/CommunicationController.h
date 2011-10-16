
#import <Foundation/Foundation.h>


@class Project;
@class WebSocketServer;
@class WebSocketConnection;

@protocol LiveReloadConnectionDelegate;

extern NSString *CommunicationStateChangedNotification;


@interface CommunicationController : NSObject {
    WebSocketServer *_server;
    NSInteger _numberOfSessions;
    NSInteger _numberOfProcessedChanges;
    NSMutableArray        *_connections;
}

+ (CommunicationController *)sharedCommunicationController;

@property(nonatomic, readonly) NSInteger numberOfSessions;

@property(nonatomic, readonly) NSInteger numberOfProcessedChanges;

- (void)startServer;

- (void)broadcastChangedPathes:(NSSet *)pathes inProject:(Project *)project;

@end


@interface LiveReloadConnection : NSObject {
@private
    WebSocketConnection   *_connection;
    BOOL                   _handshakeDone;
    BOOL                   _monitoring;
    NSInteger              _monitoringProtocolVersion;
    __weak id<LiveReloadConnectionDelegate> _delegate;
}

@property(nonatomic, assign) __weak id<LiveReloadConnectionDelegate> delegate;

@property(nonatomic, readonly) BOOL monitoring;

@end


@protocol LiveReloadConnectionDelegate <NSObject>

- (void)connectionDidFinishHandshake:(LiveReloadConnection *)connection;
- (void)connectionDidClose:(LiveReloadConnection *)connection;

@end
