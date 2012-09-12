//
//  LMSamplePlugin.m
//  SampleGeneralPlugin
//
//  Created by Victor Borshak on 24.05.07.
//  Copyright 2007 __MyCompanyName__. All rights reserved.
//

#import "LMCdToTargetPlugin.h"
#import "CdToTargetPlugin.h"


@implementation LMCdToTargetPlugin

- (NSString *) plugInName              // Name of Plugin
{
	return @"CD to target";	
}

- (unsigned) interfaceVersion          // Version protocol
{
	return 1;
}

- (NSString *) authorName              // author's name
{
	return @"iba CG";
}

- (NSString *) pluginDescription       // desription of plugin
{
	return @"Change the current Panel to the target path";
}

- (NSString *) menuItemString          // menu string
{
	return @"CD to target";	
}

- (DiskOrderPluginsType) pluginType
{
	return GENERAL_PLUGIN_TYPE;
}

- (Class) pluginClass
{
	return [CdToTargetPlugin class];
}

@end
