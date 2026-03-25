#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Frame {
public:
    static const int frameTime = 10;

    vector<unsigned char> bytes;
    int startTimestamp;
    int endTimestamp;

    Frame(int start, int end) {
        startTimestamp = start;
        endTimestamp = end;
    }
};

class Video {
    string id;
    vector<Frame> frames;
    string jsonMetaData;

public:
    Video(string vid) {
        id = vid;
    }

    void addFrame(Frame f) {
        frames.push_back(f);
    }

    Frame getFrame(int timestamp) {
        for (size_t i = 0; i < frames.size(); i++) {
            if (frames[i].startTimestamp <= timestamp &&
                frames[i].endTimestamp > timestamp) {
                return frames[i];
            }
        }

        throw out_of_range("Index out of bound exception");
    }
};

class WatchVideo {
    string id;
    string videoId;
    string userId;
    int seekTime;

public:
    WatchVideo(string i, string v, string u, int s) {
        id = i;
        videoId = v;
        userId = u;
        seekTime = s;
    }

    int getSeekTime() {
        return seekTime;
    }
};

class Database {
public:
    WatchVideo getWatchVideo(string userId, string videoId) {
        // mock data
        return WatchVideo("1", videoId, userId, 120);
    }
};

class FileSystem {
public:
    Video getVideo(string videoId) {
        Video v(videoId);

        v.addFrame(Frame(0, 10));
        v.addFrame(Frame(10, 20));
        v.addFrame(Frame(20, 30));

        return v;
    }
};

class VideoService {
private:
    FileSystem fileSystem;

public:
    Frame getFrame(string videoId, int timestamp) {
        Video video = fileSystem.getVideo(videoId);
        return video.getFrame(timestamp);
    }
};

class VideoConsumingService {
private:
    Database database;

public:
    int seekTime(string userId, string videoId) {
        WatchVideo watchVideo = database.getWatchVideo(userId, videoId);
        return watchVideo.getSeekTime();
    }
};

class User {
    string id;
    string name;
    string email;

public:
    User(string i, string n, string e) {
        id = i;
        name = n;
        email = e;
    }

    string getId() {
        return id;
    }
};

int main() {

    VideoConsumingService service;
    VideoService videoService;

    int seek = service.seekTime("user1", "video1");
    cout << "Seek Time: " << seek << endl;

    Frame frame = videoService.getFrame("video1", 15);
    cout << "Frame retrieved successfully" << endl;

    return 0;
}