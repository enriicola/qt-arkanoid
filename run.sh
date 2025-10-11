#!/bin/bash#!/bin/bash



APP_NAME=$1APP_NAME=$1



if [ -z "$APP_NAME" ]; thenif [ -z "$APP_NAME" ]; then

  echo "Usage: $0 <app-name>"  echo "Usage: $0 <app-name>"

  echo "Available: hello-world, widgets-signals"  exit 1

  exit 1fi

fi

./build-$APP_NAME/$APP_NAME

if [ ! -f "./build/$APP_NAME" ]; then
  echo "App '$APP_NAME' not found in build directory"
  echo "Try running 'make build' first"
  exit 1
fi

./build/$APP_NAME