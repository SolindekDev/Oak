const settings = require("./settings.json")
const fs = require("fs")

let deleted = 0

function main() {
    fs.readdir(settings.src_dir, (err, files) => {
        if (err)
            throw new Error("Directory of source files do not exists or program do not have permissions to read it.")

        files.forEach(file => {
            if (file.endsWith('.o')) {
                fs.unlink(settings.src_dir + file, (err) => {
                    if (err)
                    throw new Error("Can't delete file: " + file)

                })
                deleted++
            }
        });

        console.log("Successfully deleted " + deleted + " files.")
    })
}

main()
