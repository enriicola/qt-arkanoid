#!/bin/bash

APP_NAME=$1

if [ -z "$APP_NAME" ]; then
  echo "Usage: $0 <app-name>"
  exit 1
fi

./build-$APP_NAME/$APP_NAME
