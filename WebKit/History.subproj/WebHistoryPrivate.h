//
//  WebHistoryPrivate.h
//  WebKit
//
//  Created by John Sullivan on Tue Feb 19 2002.
//  Copyright (c) 2002 Apple Computer, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

#import <WebKit/WebHistory.h>

@class WebHistoryItem;

@interface WebHistoryPrivate : NSObject {
@private
    NSMutableDictionary *_entriesByURL;
    NSMutableArray *_datesWithEntries;
    NSMutableArray *_entriesByDate;
    NSURL *_URL;
}

- (id)initWithContentsOfURL: (NSURL *)URL;

- (void)addItem: (WebHistoryItem *)entry;
- (void)addItems:(NSArray *)newEntries;
- (BOOL)removeItem: (WebHistoryItem *)entry;
- (BOOL)removeItems: (NSArray *)entries;
- (BOOL)removeAllItems;

- (NSArray *)orderedLastVisitedDays;
- (NSArray *)orderedItemsLastVisitedOnDay: (NSCalendarDate *)calendarDate;
- (BOOL)containsItemForURLString: (NSString *)URLString;
- (BOOL)containsURL: (NSURL *)URL;
- (WebHistoryItem *)itemForURL:(NSURL *)URL;

- (NSURL *)URL;
- (BOOL)loadHistory;
- (BOOL)saveHistory;

@end

@interface WebHistory (WebPrivate)
- (void)removeItem: (WebHistoryItem *)entry;
- (void)addItem: (WebHistoryItem *)entry;

- (BOOL)loadHistory;
- initWithFile: (NSString *)file;
- (WebHistoryItem *)addItemForURL: (NSURL *)URL;
- (BOOL)containsItemForURLString: (NSString *)URLString;
@end
