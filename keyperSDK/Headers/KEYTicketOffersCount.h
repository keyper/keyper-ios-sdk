#import <Foundation/Foundation.h>
@class KEYOfferContainersResult;

// Provides a summary of current ticket offer counts,
// exposed by KEYSDK.shared.
@interface KEYTicketOffersCount : NSObject

// Number of all ticket offers the user currently has in INBOX or OUTGOING.
@property (assign, nonatomic, readonly) NSInteger totalOffersCount;

// Number of all ticket offers the user currently has in her INBOX.
@property (assign, nonatomic, readonly) NSInteger incomingOffersCount;

// Number of all PENDING ticket offers the user currently has in her INBOX.
@property (assign, nonatomic, readonly) NSInteger incomingPendingOffersCount;

// Number of all ticket offers the user currently has in her OUTGOING box.
@property (assign, nonatomic, readonly) NSInteger outgoingOffersCount;

// Number of all PENDING ticket offers the user currently has in her OUTGOING box.
@property (assign, nonatomic, readonly) NSInteger outgoingPendingOffersCount;

- (instancetype)initWithTotalOffersCount:(NSInteger)totalOffersCount
                     incomingOffersCount:(NSInteger)incomingOffersCount
              incomingPendingOffersCount:(NSInteger)incomingPendingOffersCount
                     outgoingOffersCount:(NSInteger)outgoingOffersCount
              outgoingPendingOffersCount:(NSInteger)outgoingPendingOffersCount;

+ (instancetype)withOfferContainersResult:(KEYOfferContainersResult *)offerContainersResult;

@end
