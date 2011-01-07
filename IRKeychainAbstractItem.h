//
//  IRKeychainAbstractItem.h
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychainDefines.h"
//	

@interface IRKeychainAbstractItem : NSObject <NSCoding>

- (id) initWithIdentifier:(NSString *)identifier;

//	Makes a new object, which is not synced.


- (id) initWithContentsOfSecurityItemDictionary:(NSDictionary *)dictionary;

//	Makes a new object and fills its values using the reference.  Subclasses should override this method and be stricter in acceptance.


- (BOOL) synchronizeWithError:(NSError **)error overwrittingOriginal:(BOOL)shouldOverwrite;

//	Synchronize the item with the keychain services.  Returns a BOOL that indicates success or failure.
//	If shouldOverwrite is YES, overwrites the original.


- (BOOL) synchronize;

//	return [self synchronizeWithErorr:nil overwrittingOriginal:YES]


- (BOOL) removeWithError:(NSError **)error;

//	Removes the item from the keychain.  Returns a BOOL that indicates success or failure.


- (BOOL) remove;

//	return [self removeWithError:nil];


- (NSDictionary *) securityItemQueryDictionary;

//	Returns a dictionary which contains useful and comforming information gathered from the item’s properties, to be used by the shared keychain manager.
//	Subclasses wishing to make modifications shall merge with the superclass’s response.


- (NSDictionary *) securityItemAttributesDictionary;

//	Returns a dictionary containing security attributes (e.g. IRKeychainItem properties) of the item, to be used when updating or creating an item.
//	Subclasses wishing to make modifications shall merge with the superclass’s response.


- (NSDictionary *) descriptionDictionary;

//	Returns a dictionary that is used in the custom description method.  Made available so logging is complete.





@property (nonatomic, readwrite, assign) IRKeychainItemAccessCondition accessCondition;
@property (nonatomic, readwrite, assign) NSString *accessGroup;





@property (nonatomic, readonly, retain) NSString *identifier;

//	Represents a single identifier field, may be nil in subclasses if not applicable


@property (nonatomic, readwrite, retain) NSData *secret;
@property (nonatomic, readwrite, retain) NSString *secretString;

//	Represnts the decoded object (from NSData) to key kSecValueData.
//	secretString is piggiedback to secret.


@property (nonatomic, readonly, retain) NSData *persistentReference;

//	Represents a persistent representation that can be used to find the exact item from the keychain.  Made by SecKeychainItemCreatePersistentReference().





@end
