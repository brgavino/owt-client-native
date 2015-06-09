/*
 * Intel License
 */

#include "talk/woogeen/sdk/base/stream.h"
#include "talk/woogeen/sdk/base/peerconnectiondependencyfactory.h"

namespace woogeen {

Stream::Stream() : id_(""){
}

Stream::Stream(std::string& id) : id_(id){
}

scoped_refptr<MediaStreamInterface> Stream::MediaStream() {
  CHECK(media_stream_);
  return media_stream_;
}

void Stream::MediaStream(scoped_refptr<MediaStreamInterface> media_stream) {
  CHECK(media_stream);
  media_stream_=media_stream;
}

std::string& Stream::Id(){
  return id_;
}

std::shared_ptr<LocalCameraStream> LocalCameraStream::Create(cricket::VideoCapturer* capturer) {
  std::shared_ptr<LocalCameraStream> local_camera_stream(new LocalCameraStream(capturer));
  return local_camera_stream;
}

LocalCameraStream::LocalCameraStream(cricket::VideoCapturer* capturer) {
  scoped_refptr<PeerConnectionDependencyFactory> factory = PeerConnectionDependencyFactory::Get();
  media_constraints_.SetMandatory(webrtc::MediaConstraintsInterface::kMaxWidth, "320");
  media_constraints_.SetMandatory(webrtc::MediaConstraintsInterface::kMaxHeight, "240");
  media_stream_=factory->CreateLocalMediaStream("mediastream", capturer, &media_constraints_);
}

RemoteStream::RemoteStream(MediaStreamInterface* media_stream, std::string& from)
    : remote_user_id_(from){
  media_stream_=media_stream;
}

RemoteStream::RemoteStream(std::string& id, std::string& from)
    : Stream(id),
      remote_user_id_(from) {
}
std::string& RemoteStream::From(){
  return remote_user_id_;
}

void RemoteStream::MediaStream(scoped_refptr<MediaStreamInterface> media_stream){
  media_stream_=media_stream;
}

scoped_refptr<MediaStreamInterface> RemoteStream::MediaStream() {
  return media_stream_;
}

RemoteCameraStream::RemoteCameraStream(std::string& id, std::string& from) : RemoteStream(id, from) {
}

RemoteCameraStream::RemoteCameraStream(MediaStreamInterface* media_stream, std::string& from) : RemoteStream(media_stream, from) {
}

RemoteScreenStream::RemoteScreenStream(std::string& id, std::string& from) : RemoteStream(id, from) {
}

RemoteScreenStream::RemoteScreenStream(MediaStreamInterface* media_stream, std::string& from) : RemoteStream(media_stream, from) {
}

}