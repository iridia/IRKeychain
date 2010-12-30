//
//  IRKeychainAbstractItem.m
//  IRKeychain
//
//  Created by Evadne Wu on 12/30/10.
//  Copyright 2010 Iridia Productions. All rights reserved.
//

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

- (id) initWithCoreFoundationReference:(CFTypeRef)reference {

//	FIXME
	
	return [self initWithIdentifier:nil];

}

- (void) dealloc {

	self.identifier = nil;
	
	[super dealloc];

}





- (NSString *) description {

	return [[super description] stringByAppendingFormat:@"(identifier = %@)", self.identifier];

}





- (BOOL) synchronizeWithError:(NSError **)error overwrittingOriginal:(BOOL)shouldOverwrite {

	NSLog(@"Synchronizing keychain item %@", self);
	
	return NO;

}





@end
