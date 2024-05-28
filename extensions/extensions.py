name = input("File name: ")
name = name.lower()

if ".gif" in name:
    print("image/gif")
elif ".jpg" in name:
    print("image/jpeg")
elif ".jpeg" in name:
    print("image/jpeg")
elif ".png" in name:
    print("image/png")
elif ".pdf" in name:
    print("application/pdf")
elif ".txt" in name:
    name = name.removesuffix(".txt")
    print("text/" + name)
elif ".zip" in name:
    print("application/zip")
else:
    print("application/octet-stream")
