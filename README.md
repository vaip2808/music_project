
# 🎵 Music Streaming App

A simple C++ console application that manages songs, albums, artists, and playlists — simulating a basic music streaming service.

## 🚀 Features

- Add and manage **Songs**, **Albums**, and **Artists**
- View songs by album or artist
- Create and manage custom **Playlists**
- Store data persistently using `.txt` files
- Console-based interface for easy interaction

## 📁 Project Structure

```
music_app/
├── main.cpp                  # Entry point
├── music_app.cpp             # Core implementation
├── music_streaming_app.cpp   # Playlist and streaming logic
├── music_app.hpp             # Class & function declarations
├── songs.txt                 # Song data
├── albums.txt                # Album data
├── artists.txt               # Artist data
├── Makefile                  # Build instructions
├── app.exe                   # Compiled executable (Windows)
├── *.o                       # Object files
```

## ⚙️ Build Instructions

### Using Make (Recommended)

```bash
make
./app    # or ./app.exe on Windows
```

### Manual Compilation

```bash
g++ main.cpp music_app.cpp music_streaming_app.cpp -o app
./app
```

## 📚 File Descriptions

- `songs.txt`: List of all songs with details (title, duration, artist, album)
- `albums.txt`: Album names and metadata
- `artists.txt`: Artist names and their associated albums/songs

## 🛠 Technologies Used

- C++ (OOP and file handling)
- Make (for compilation automation)

## ✅ To-Do / Future Enhancements

- Add song search functionality
- Implement save/load playlist feature
- Add support for duration filtering or sorting

---

> Created by Vaibhav Pawar ❤️  
