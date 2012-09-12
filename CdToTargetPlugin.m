//
//  LMSampleGeneralPlugin.m
//  SampleGeneralPlugin
//
//  Created by Victor Borshak on 24.05.07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import "CdToTargetPlugin.h"


@implementation CdToTargetPlugin

- (BOOL) shouldAppeaarInToolbar
{
	return YES;
}

- (NSString *) toolBarIconName
{
	return @"APPL.tiff";
}

- (NSString *) uniqueIdentifier
{
	return @"de.ibacg.diskorder.openInOtherPanelPlugin";
}

- (int) startOperationWithPaths:(NSArray *)paths diskOrder:(id)diskOrder
{
    //	if (paths && [paths count]>0) {
    //		BOOL isDir = NO;
    //		if ([[NSFileManager defaultManager] fileExistsAtPath:[paths objectAtIndex:0] isDirectory:&isDir] && !isDir)
    //			[diskOrder editFileAtPath:[paths objectAtIndex:0]];
    //		else NSRunAlertPanel(@"Folder is selected", @"Looks like you've selected a folder. Please select a file and try again!",@"Close",nil,nil);
    //	} else NSRunAlertPanel(@"Nothing selected", @"It seems that nothing is selected!",@"Close",nil,nil);
    //
    //	return 0;
           [diskOrder switchDiskOrderToPath:[diskOrder targetPath]];
    
    return 0;
}

- (BOOL) shouldAutostart
{
	return NO;
}

- (BOOL) shouldAppearInExtrasMenu
{
	return YES;
}

- (BOOL) allowsManyInstances
{
	return YES;
}

- (void) unload
{
	[self release];	
}

@end
