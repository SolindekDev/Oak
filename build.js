const settings = require("./settings.json")
const fs = require("fs")
const { exec } = require("child_process")

function add_exe_end() {
  return process.platform == "win32" ? ".exe" : ""
}

function main() {
    console.clear()
    fs.readdir(settings.src_dir, (err, files) => {
        if (err)
            throw new Error("Directory of source files do not exists or program do not have permissions to read it.")

        let already_deleted = 0
        let already_compiled = 0
        let objs = []

        console.log(`\x1b[0;32mOAK\x1b[0m: Compiling all files to objects... [\x1b[0;33m${already_compiled}\x1b[0m / \x1b[0;33m${files.length}\x1b[0m]`)
        for (let i = 0; i < files.length; i++) {
            exec(`${settings.cc} -c -g ${settings.cc_flags} ${settings.src_dir + files[i]} -o ${settings.src_dir + files[i].replace(".cpp", ".o")}`, (error, stdout, stderr) => {
                if (error) { console.clear(); console.log(`${error.message}`); process.exit(1) }
                if (stderr) { console.clear(); console.log(`${stderr}`); process.exit(1) }
                already_compiled++
                objs.push(settings.src_dir + files[i].replace(".cpp", ".o"))
                console.clear()
                console.log(`\x1b[0;32mOAK\x1b[0m: Compiling all files to objects... [\x1b[0;33m${already_compiled}\x1b[0m / \x1b[0;33m${files.length}\x1b[0m]`)
                if (already_compiled == files.length) {
                    console.log(`\x1b[0;32mOAK\x1b[0m: Linking objects to executable file [\x1b[0;33m0\x1b[0m / \x1b[0;33m1\x1b[0m]`)
                    exec(`${settings.cc} ${settings.cc_flags} ${objs.join(" ")} -o ${settings.output + add_exe_end()}`, (error, stdout, stderr) => {
                        if (error) { console.clear(); console.log(`${error.message}`); process.exit(1) }
                        if (stderr) { console.clear(); console.log(`${stderr}`); process.exit(1) }
                        console.log(`\x1b[0;32mOAK\x1b[0m: Linking objects to executable file [\x1b[0;33m1\x1b[0m / \x1b[0;33m1\x1b[0m]`)
                        console.log(`\x1b[0;32mOAK\x1b[0m: Cleaning object files... `)
                        for (let i1 = 0; i1 < files.length; i1++) {
                            already_deleted++
                            fs.unlink(objs[i1], (err) => {
                                if (err) throw err;
                            })
                            if (already_deleted == objs.length)
                              console.log(`\x1b[0;32mOAK\x1b[0m: Output in ${settings.output + add_exe_end()}`)
                        }
                    })
                }
            })
        }

    })
}

main()
