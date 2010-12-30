//
//  IRKeychainManager.h
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychain.h"


@interface IRKeychainManager : NSObject

+ (IRKeychainManager *) sharedManager;

- (NSArray *) keychainItemsOfKind:(IRKeychainItemKind)kind matchingPredicate:(NSDictionary *)predicateOrNil inAccessGroup:(NSString *)accessGroupOrNil;

//	Returns an array of items matching a certain predicate that is the same thing you can pass to SecItemCopyMatching().  Item order not guaranteed.


//	- (NSArray *) passwordsMatchingLabel:predicate:inAccessGroup:
//	- (NSArray *) internetPasswordsMatchingServer:account:predicate:inAccessGroup:

@property (nonatomic, readwrite, retain) NSString *defaultAccessGroupName;

@end
