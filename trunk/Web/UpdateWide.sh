#!/bin/bash
set -x
set -e
rm -rf /tmp/WideUpdate
mkdir /tmp/WideUpdate
cd /tmp/WideUpdate
wget --user="$(cat ~/.loungecpp/user | base64 -d)" --password="$(cat ~/.loungecpp/password | base64 -d)" http://ci.loungecpp.net/repository/download/WideDefault/.lastFinished/Wide/Deployment/Wide.zip
(set -x ; mkdir Wide ; cd Wide ; unzip ../Wide.zip)
chown -R root:root Wide
chmod 755 Wide/CLI
rm -rf /usr/local/bin/Wide
mv Wide /usr/local/bin/
