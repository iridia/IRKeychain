//
//  IRKeychainPasswordItem.h
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychain.h"


@interface IRKeychainPasswordItem : IRKeychainAbstractItem

@property (nonatomic, readonly, retain) NSDate *creationDate;
@property (nonatomic, readonly, retain) NSDate *lastModificationDate;

//	Note that before an item is synced to the keychain, these dates could be nil.


@property (nonatomic, readwrite, retain) NSNumber *creatorCodeRepresentation;

@property (nonatomic, readwrite, assign, getter=isInvisible) BOOL invisible;
@property (nonatomic, readwrite, assign, getter=isNegative) BOOL negative;

@property (nonatomic, readwrite, retain) NSString *associatedAccountName;
@property (nonatomic, readwrite, retain) NSString *associatedServiceName;

@property (nonatomic, readwrite, retain) NSString *userDescription;
@property (nonatomic, readwrite, retain) NSString *userComment;

@property (nonatomic, readwrite, retain) NSString *userLabel;
@property (nonatomic, readwrite, retain) NSData *userGenericData;

@end
