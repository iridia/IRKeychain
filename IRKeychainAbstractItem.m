//
//  IRKeychainAbstractItem.m
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

#import "IRKeychain.h"
#import "IRKeychainAbstractItem.h"


@interface IRKeychainAbstractItem ()

@property (nonatomic, readwrite, retain) NSString *identifier;
@property (nonatomic, readwrite, retain) NSData *persistentReference;

@end





@implementation IRKeychainAbstractItem

@synthesize accessCondition, accessGroup, identifier, secret, secretString;
@synthesize persistentReference;

- (id) init {

	return [self initWithIdentifier:nil];

}

- (id) initWithIdentifier:(NSString *)inIdentifier {

	self = [super init]; if (!self) return nil;
	
	self.identifier = inIdentifier;
	
	return self;

}

- (id) initWithContentsOfSecurityItemDictionary:(NSDictionary *)dictionary {

	self = [self initWithIdentifier:nil]; if (!self) return nil;
	
	self.secret = [dictionary objectForKey:(id)kSecValueData];
	
	self.persistentReference = (NSData *)[dictionary objectForKey:(id)kSecValuePersistentRef];
	
	return self;

}

- (id) initWithCoder:(NSCoder *)aDecoder {

	self = [self init]; if (!self) return nil;
	
	self.accessCondition = [aDecoder decodeIntForKey:@"accessCondition"];
	self.accessGroup = [aDecoder decodeObjectForKey:@"accessGroup"];
	self.identifier = [aDecoder decodeObjectForKey:@"identifier"];

//	Actually, this is to be retrieved manually
//	self.secret = [aDecoder decodeObjectForKey:@"secret"];

	self.persistentReference = [aDecoder decodeObjectForKey:@"persistentReference"];
	
	self.secret = self.persistentReference ? [[IRKeychainManager sharedManager] secretFromPersistentReference:self.persistentReference] : nil;
	
	return self;

}

- (void) encodeWithCoder:(NSCoder *)aCoder {

	[aCoder encodeInt:self.accessCondition forKey:@"accessCondition"];
	[aCoder encodeObject:self.accessGroup forKey:@"accessGroup"];
	[aCoder encodeObject:self.identifier forKey:@"identifier"];
	[aCoder encodeObject:self.persistentReference forKey:@"persistentReference"];

}

- (void) dealloc {

	self.accessGroup = nil;
	self.identifier = nil;
	self.secret = nil;
	self.persistentReference = nil;
	
	[super dealloc];

}





- (NSDictionary *) securityItemQueryDictionary {

	NSMutableDictionary *returnedDictionary = [NSMutableDictionary dictionary];
	
	[returnedDictionary setObject:(id)SecClassFromIRKeychainItemKind(IRKeychainItemKindFromClass([self class])) forKey:(id)kSecClass];
	
	return returnedDictionary;

}

- (NSDictionary *) securityItemAttributesDictionary {

	NSMutableDictionary *returnedDictionary = [NSMutableDictionary dictionary];
	
	[returnedDictionary setObject:(id)SecClassFromIRKeychainItemKind(IRKeychainItemKindFromClass([self class])) forKey:(id)kSecClass];
	
	[returnedDictionary setObject:self.secret forKey:(id)kSecValueData];
	
	return returnedDictionary;

}





- (BOOL) synchronizeWithError:(NSError **)error overwrittingOriginal:(BOOL)shouldOverwrite {

	//	Do not use the absense of a persistent data as an excuse
	
	BOOL itemExists = (BOOL)!!self.persistentReference;
	
	if (!itemExists)
		itemExists = ([[[IRKeychainManager sharedManager] keychainItemsOfKind:IRKeychainItemKindFromClass([self class]) matchingPredicate:[self securityItemQueryDictionary] inAccessGroup:self.accessGroup] count] > 0);
	
	OSStatus result;
	
	if (itemExists) {
	
		if (!shouldOverwrite) {
		
			if (error != nil)
			*error = [NSError errorWithDomain:[IRKeychainManager sharedManager].errorDomain code:0 userInfo:[NSDictionary dictionaryWithObject:@"Not going to overwrite existing item during synchronization.  Set shouldOverwrite to YES." forKey:@"explanation"]];
			
			return NO;
		
		}
		
		NSMutableDictionary *attributesDictionary = [[[self securityItemAttributesDictionary] mutableCopy] autorelease];
		[attributesDictionary removeObjectForKey:(id)kSecClass];
			
		result = SecItemUpdate(
		
			(CFDictionaryRef)[self securityItemQueryDictionary],
			(CFDictionaryRef)attributesDictionary
			
		);
		
		if (result == errSecSuccess) {
			
			NSLog(@"Error: %@", irNSStringFromOSStatus(result));
			itemExists = NO;	//	Abandon it.
			self.persistentReference = nil;	//	?
		
		} else {
			
			if (!self.persistentReference)
				self.persistentReference = ((IRKeychainAbstractItem *)[[[IRKeychainManager sharedManager] keychainItemsOfKind:IRKeychainItemKindFromClass([self class]) matchingPredicate:[self securityItemQueryDictionary] inAccessGroup:nil] objectAtIndex:0]).persistentReference;
			
		}
		
	}
	
	if (!itemExists) {
	
		NSData *resultData;
				
		result = SecItemAdd(
		
			(CFDictionaryRef)((^ {
			
				NSMutableDictionary *returnedDictionary = [[self securityItemAttributesDictionary] mutableCopy];
				
				[returnedDictionary setObject:(id)kCFBooleanTrue forKey:(id)kSecReturnPersistentRef];
				
				return returnedDictionary;
			
			})()),
			
			(CFTypeRef *)&resultData
		
		);
				
		if (result == errSecSuccess) {

			NSAssert([resultData isKindOfClass:[NSData class]], @"What returned by SecItemAdd() is not NSData / CFDataRef.  Check query parameters!");
			self.persistentReference = resultData;
		
		}
		
	}
	
	if (result == errSecSuccess) return YES;
	
	if (error != nil) {

		*error = [NSError errorWithDomain:[IRKeychainManager sharedManager].errorDomain code:(int)result userInfo:[NSDictionary dictionaryWithObject:irNSStringFromOSStatus(result) forKey:@"explanation"]];
		
		NSLog(@"Error. %@", *error);
		
	} else {
	
		NSLog(@"Error. %@", irNSStringFromOSStatus(result));
	
	}
	
	return NO;

}

- (BOOL) synchronize {

	return [self synchronizeWithError:nil overwrittingOriginal:YES];

}





- (BOOL) removeWithError:(NSError **)error {

//	If the item was already in the keychain, make it so that it is always referenced just by the existing ref, so as to avoid kludgy searching

//	if (self.persistentReference)
//	[searchDictionary setObject:self.persistentReference forKey:(id)kSecValuePersistentRef];

	return NO;

}

- (BOOL) remove {

	return [self removeWithError:nil];

}





- (NSString *) secretString {

	return [[[NSString alloc] initWithData:self.secret encoding:NSUTF8StringEncoding] autorelease];

}

- (void) setSecretString:(NSString *)inSecretString {

	self.secret = [inSecretString dataUsingEncoding:NSUTF8StringEncoding];

}





- (NSDictionary *) descriptionDictionary {

	return [NSDictionary dictionaryWithObjectsAndKeys:
	
		IRKeychainObjectOrNull(self.identifier), @"identifier",
		IRKeychainObjectOrNull(self.secret), @"secret",
		IRKeychainObjectOrNull(self.persistentReference), @"persistentReference",
	
	nil];

}

- (NSString *) description {

	NSMutableArray *descriptionDictionaryStrings = [NSMutableArray array];
	NSDictionary *descriptionDictionary = [self descriptionDictionary];
	
	for (id aKey in descriptionDictionary)
	[descriptionDictionaryStrings addObject:[NSString stringWithFormat:
	
		@"%@ = %@",
		aKey,
		[descriptionDictionary objectForKey:aKey]
	
	]];

	return [NSString stringWithFormat:@"%@ { %@ }",
	
		[super description],
		[descriptionDictionaryStrings componentsJoinedByString:@", "]
		
	];

}





@end
