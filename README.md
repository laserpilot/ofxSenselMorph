# ofxSenselMorph
openFrameworks addon for Sensel Morph (private currently - will change on public release)

Built with openFrameworks 0.8.4 and OSX 10.10.5 + XCode 6.4

Simple example making use of the sensel C++ API

THIS IS A WORK IN PROGRESS!! Still waiting for the API to stabilize as this was made with a prototype unit. Could use a lot of refactoring and some smarter memory management techniques.

Currently only works with OSX - but it should be easy to adapt to Linux or Windows.

If you're using the addon on a new app - I left the windows .cpp file in there for now but you will need to manually remove just "sensel_serial_win.cpp" from your Xcode project if you want it to work with OSX

**To do:**

 - Windows examples
 - Add support for LED control
 - Smarter memory management
 - Support for multiple units
 - Update to latest API
 - 
 
The MIT License (MIT)
Copyright (c) 2015 Fake Love Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
