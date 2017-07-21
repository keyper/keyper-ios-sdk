#
# Be sure to run `pod lib lint keyper-ios-sdk.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'keyper-ios-sdk'
  s.version          = '1.0.0'
  s.summary          = 'iOS SDK for keyper.io - ticketing with friends.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
Integrate a full ticketing solution by using this SDK.
                       DESC

  s.homepage                = 'https://github.com/keyper/keyper-ios-sdk'
  s.license                 = { :type => 'MIT', :file => 'LICENSE' }
  s.author                  = { 'Manuel Maly' => 'manuel.maly@gmail.com' }
  s.social_media_url        = 'https://twitter.com/keyper'

  s.platforms               = { :ios => '8.0' }
  s.source                  = { :git => 'https://github.com/keyper/keyper-ios-sdk.git', :tag => s.version.to_s }

  s.source_files            = 'keyper-ios-sdk/*.h'
  s.vendored_libraries      = 'keyper-ios-sdk/libkeyper-ios-sdk.a'
  s.resources               = ['keyper-ios-sdk/*.bundle']
  s.public_header_files     = 'keyper-ios-sdk/*.h'
  s.preserve_paths          = 'keyper-ios-sdk/*'
  
  s.frameworks  = 'Foundation', 'UIKit', 'MapKit', 'EventKit', 'EventKitUI', 'AddressBook', 'CoreGraphics', 'CoreLocation', 'CoreImage', 'AVFoundation', 'ImageIO', 'MessageUI', 'SystemConfiguration', 'MobileCoreServices', 'Accelerate'
  s.library     = 'xml2', 'z'
end
