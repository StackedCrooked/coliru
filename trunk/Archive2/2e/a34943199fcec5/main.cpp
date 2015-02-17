

class Thumbnailer
message ThumbnailOptions   (ClipSegmentationOptions, etc. part of the same proto)

refactor FilterThumbnailOptions into ThumbnailOptions (keep all streams in the filter, rest goes out)


inputs:
keep the unpacking from Process and just call AddFrame.

main API:
void Thumbnailer::AddFrame(cv::Mat frame, CameraMotion camera_motion, RegionFlowFeatureList features, SalientPointFrame saliency, ToneChange);


on Close just call GetThumbnail()

output:
// get a proto for every added frame, 1:1 mapping   // TODO: Add frame counter to it, only return the actual thumbnails.
void Thumbnailer::GetThumbnail(std::vector<ThumbnailFrame>* frames);


run existing stuff over some files:
for f in ~/x20/Videos/shake_dataset/*; do ./blaze-bin/video/content_analysis/motion_stabilization/motion_stabilization_tree_sample --input_file=$f --filter_tree_file=video/content_analysis/motion_stabilization/filter_trees/thumbnail_tree.pbtxt --output_dir=/grundman/Projects --alsologtostderr --ffmpeg_pts_from_framenum; done
