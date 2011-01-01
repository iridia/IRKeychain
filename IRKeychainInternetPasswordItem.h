//
//  IRKeychainInternetPasswordItem.h
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychain.h"


@interface IRKeychainInternetPasswordItem : IRKeychainAbstractItem

@property (nonatomic, readonly, retain) NSDate *creationDate;
@property (nonatomic, readonly, retain) NSDate *lastModificationDate;

//	Note that before an item is synced to the keychain, these dates could be nil.


@property (nonatomic, readwrite, retain) NSNumber *creatorCodeRepresentation;

@property (nonatomic, readwrite, retain) NSString *associatedAccountName;

@property (nonatomic, readwrite, retain) NSString *userDescription;
@property (nonatomic, readwrite, retain) NSString *userComment;

@property (nonatomic, readwrite, retain) NSString *userLabel;

@property (nonatomic, readwrite, retain) NSString *serverSecurityDomain;
@property (nonatomic, readwrite, retain) NSString *serverAddress;
@property (nonatomic, readwrite, retain) NSNumber *serverPort;
@property (nonatomic, readwrite, assign) IRKeychainProtocol serverProtocol;
@property (nonatomic, readwrite, assign) IRKeychainAuthenticationType serverAuthenticationType;
@property (nonatomic, readwrite, retain) NSString *serverPath;

@property (nonatomic, readonly, copy) NSURL *representedURL;	// = serverAddress + port + path

@end
