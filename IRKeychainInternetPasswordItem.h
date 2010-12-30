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
@property (nonatomic, readwrite, retain) NSData *userGenericData;

@property (nonatomic, readwrite, retain) NSString *internetSecurityDomain;
@property (nonatomic, readwrite, retain) NSString *serverAddress;
//	@property (nonatomic, readwrite, assign) SecProtocolType protocol;
@property (nonatomic, readwrite, assign) IRKeychainAuthenticationType authenticationType;	//kSecAttrAuthenticationType
@property (nonatomic, readwrite, retain) NSNumber *port;	//kSecAttrAuthenticationType
@property (nonatomic, readwrite, retain) NSString *path;	//kSecAttrAuthenticationType

@property (nonatomic, readonly, copy) NSURL *representedURL;	// = serverAddress + port + path

@end
