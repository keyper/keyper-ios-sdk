#
# Be sure to run `pod lib lint keyper-ios-sdk.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'keyper-ios-sdk'
  s.version          = '0.9.0'
  s.summary          = 'iOS SDK for keyper.io - ticketing with friends.'

# This description is used to generate tags and improve search results.
#   * Think: What does it do? Why did you write it? What is the focus?
#   * Try to keep it short, snappy and to the point.
#   * Write the description between the DESC delimiters below.
#   * Finally, don't worry about the indent, CocoaPods strips it!

  s.description      = <<-DESC
TODO: Add long description of the pod here.
                       DESC

  s.homepage                = 'https://github.com/keyper/keyper-ios-sdk'
  s.license                 = { :type => 'MIT', :file => 'LICENSE' }
  s.author                  = { 'Manuel Maly' => 'manuel.maly@gmail.com' }
  s.social_media_url        = 'https://twitter.com/keyper'

  s.platforms               = { :ios => '8.0' }
  s.source                  = { :http => 'https://bintray.com/keyper/generic/download_file?file_path=io/keyper/ios/keyper-ios-sdk_0.9.zip', :type => 'zip' }
  s.source_files            = '*.h'

  # s.public_header_files     = 'keyper-ios-sdk/Library/*.h'

  s.preserve_paths      = 'libkeyper-ios-sdk-source.a'
  s.vendored_libraries  = 'libkeyper-ios-sdk-source.a'
  s.resources           = ['*.bundle']
  
  s.frameworks  = 'Foundation', 'UIKit', 'MapKit', 'EventKit', 'EventKitUI', 'AddressBook', 'CoreGraphics'

end
