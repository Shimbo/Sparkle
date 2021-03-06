//
//  SUUpdateDriver.h
//  Sparkle
//
//  Created by Andy Matuschak on 5/7/08.
//  Copyright 2008 Andy Matuschak. All rights reserved.
//

#ifndef SUUPDATEDRIVER_H
#define SUUPDATEDRIVER_H

#if __has_feature(modules)
@import Cocoa;
#else
#import <Cocoa/Cocoa.h>
#endif
#import "SUExport.h"
extern NSString *const SUUpdateDriverFinishedNotification;
@class SUAppcastItem, SPUDownloader;
@class SUHost, SUUpdater;
@protocol SUUpdaterPrivate;
SU_EXPORT @interface SUUpdateDriver : NSObject

@property (strong) SUAppcastItem *updateItem;
@property (strong) SPUDownloader *download;


// We only have SUUpdater* forward declared intentionally (i.e, not #import'ing SUUpdater.h in the update drivers)
// This is so we can minimize what we can access using SUUpdaterPrivate
@property (readonly, weak) SUUpdater<SUUpdaterPrivate> *updater;

@property (strong) SUHost *host;

- (instancetype)initWithUpdater:(id<SUUpdaterPrivate>)updater;
- (void)checkForUpdatesAtURL:(NSURL *)URL host:(SUHost *)host domain:(NSString *)domain;
- (void)abortUpdate;
/** If there is an update waiting to be installed, show UI indicating so. Return NO otherwise (e.g. if it's not supported). */
- (BOOL)resumeUpdateInteractively;
- (void)showAlert:(NSAlert *)alert;

@property (getter=isInterruptible, readonly) BOOL interruptible;
@property (readonly) BOOL finished;
@property (readonly) BOOL downloadsAppcastInBackground;
@property (readonly) BOOL downloadsUpdatesInBackground;
@property BOOL automaticallyInstallUpdates;

@end

#endif
