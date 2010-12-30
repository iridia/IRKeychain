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

@end





@implementation IRKeychainAbstractItem

- (id) init {

	return [self initWithIdentifier:nil];

}

- (id) initWithIdentifier:(NSString *)inIdentifier {

	self = [super init]; if (!self) return nil;
	
	self.identifier = inIdentifier;
	
	return self;

}

- (id) initWithContentsOfSecurityItemDictionary:(NSDictionary *)dictionary {

	NSLog(@"initWithContentsOfSecurityItemDictionary %@", dictionary);

	self = [self initWithIdentifier:nil]; if (!self) return nil;
	
//	Configure item with some more informtion from the passed dictionary
	
	return self;

}

- (void) dealloc {

	self.identifier = nil;
	
	[super dealloc];

}





- (NSString *) description {

	return [[super description] stringByAppendingFormat:@"(identifier = %@)", self.identifier];

}





- (NSDictionary *) securityItemQueryDictionary {

	NSMutableDictionary *returnedDictionary = [NSMutableDictionary dictionary];
	
	[returnedDictionary setObject:(id)SecClassFromIRKeychainItemKind(IRKeychainItemKindFromClass([self class])) forKey:(id)kSecClass];
	
	return returnedDictionary;

}

- (NSDictionary *) securityItemAttributesDictionary {

	NSMutableDictionary *returnedDictionary = [NSMutableDictionary dictionary];
	
	[returnedDictionary setObject:(id)SecClassFromIRKeychainItemKind(IRKeychainItemKindFromClass([self class])) forKey:(id)kSecClass];
	
	[returnedDictionary setObject:(id)[self.secret dataUsingEncoding:NSUTF8StringEncoding] forKey:(id)kSecValueData];
	
	return returnedDictionary;

}





- (BOOL) synchronizeWithError:(NSError **)error overwrittingOriginal:(BOOL)shouldOverwrite {

	NSLog(@"Synchronizing keychain item %@", self);
	NSLog(@"[self securityItemQueryDictionary] %@", [self securityItemQueryDictionary]);
	NSLog(@"[self securityItemAttributesDictionary] %@", [self securityItemAttributesDictionary]);
	
	BOOL itemExists = ([[[IRKeychainManager sharedManager] keychainItemsOfKind:IRKeychainItemKindFromClass([self class]) matchingPredicate:[self securityItemQueryDictionary] inAccessGroup:self.accessGroup] count] > 0);
	
	OSStatus result;
	
	if (itemExists) {
	
		if (!shouldOverwrite) {
		
			if (error != nil)
			*error = [NSError errorWithDomain:[IRKeychainManager sharedManager].errorDomain code:0 userInfo:[NSDictionary dictionaryWithObject:@"Not going to overwrite existing item during synchronization.  Set shouldOverwrite to YES." forKey:@"explanation"]];
			
			return NO;
		
		}
		
		NSLog(@"Updating result");
		
		NSMutableDictionary *attributesDictionary = [[self securityItemAttributesDictionary] mutableCopy];
		[attributesDictionary removeObjectForKey:(id)kSecClass];
	
		result = SecItemUpdate(
		
			(CFDictionaryRef)[self securityItemQueryDictionary],
			(CFDictionaryRef)attributesDictionary
			
		);
		
	} else {
	
		NSLog(@"Adding result");
	
		result = SecItemAdd(
		
			(CFDictionaryRef)[self securityItemAttributesDictionary], 
			NULL
		
		);
	
	}
	
	NSLog(@"Result %@", irNSStringFromOSStatus(result));
	
	if (result == errSecSuccess) return YES;
	
	if (error != nil) {

		*error = [NSError errorWithDomain:[IRKeychainManager sharedManager].errorDomain code:(int)result userInfo:[NSDictionary dictionaryWithObject:irNSStringFromOSStatus(result) forKey:@"explanation"]];
		
		NSLog(@"Error. %@", *error);
		
	}
	
	return NO;

}

- (BOOL) synchronize {

	return [self synchronizeWithError:nil overwrittingOriginal:YES];

}





- (BOOL) removeWithError:(NSError **)error {

	return NO;

}

- (BOOL) remove {

	return [self removeWithError:nil];

}





@end
