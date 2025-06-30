#pragma once
#include <string>
#include <vector>
#include <map>
#include <set>

class Entity {
public:
    virtual std::string getId() const = 0;
};

class Song;
class Artist : public Entity {
public:
    std::string id, name, genre;
    std::set<std::string> songIds;
    std::string getId() const override;
};

class Album : public Entity {
public:
    std::string id, title;
    int releaseYear;
    std::vector<std::string> songIds;
    std::string getId() const override;
};

class Song : public Entity {
public:
    std::string id, title, albumId;
    int duration;
    std::vector<std::string> artistIds;
    std::string getId() const override;
};

class Playlist : public Entity {
public:
    std::string id, name;
    std::vector<std::string> songIds;
    std::string getId() const override;
};

extern std::map<std::string, Song> songs;
extern std::map<std::string, Album> albums;
extern std::map<std::string, Artist> artists;
extern std::map<std::string, Playlist> playlists;

void loadArtists(const std::string&);
void loadAlbums(const std::string&);
void loadSongs(const std::string&);
void displayAllArtists();
void displayAllAlbums();
void displayAllSongs();
void createPlaylist();
void updatePlaylist();
void deletePlaylist();
void listPlaylists();
void playlistMenu();
