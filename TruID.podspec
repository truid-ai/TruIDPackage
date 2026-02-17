Pod::Spec.new do |s|
  s.name         = "TruID"
  s.version      = "1.0.0"
  s.summary      = "TruID SDK for identity verification"
  s.description  = <<-DESC
                   TruID SDK provides identity verification capabilities including
                   face liveness detection, document capture, and biometric authentication.
                   DESC
  s.homepage     = "https://truid.ai"
  s.license      = { :type => "MIT", :file => "LICENSE" }
  s.authors      = { "TruID" => "dev@truid.ai" }
  
  # Platform support
  s.platform     = :ios, "15.0"
  s.ios.deployment_target = "15.0"
  
  # Source location
  s.source       = { :git => ".", :tag => "#{s.version}" }
  
  # The xcframework
  s.vendored_frameworks = "Sources/TruID.xcframework"
  
  # Swift version
  s.swift_version = "5.6"
  
  # Framework dependencies (if TruID needs any system frameworks)
  s.frameworks = "UIKit", "Foundation", "SwiftUI"
  
  # Note: This xcframework currently only supports physical devices (ios-arm64)
  # Simulator builds will fail unless a simulator slice is added to the xcframework
  s.pod_target_xcconfig = {
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64 x86_64'
  }
  s.user_target_xcconfig = {
    'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64 x86_64'
  }
end

