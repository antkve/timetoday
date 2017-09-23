# timetoday
a set of scripts for monitoring window tag usage for awesome-window-manager

These are some scripts I wrote for a little blue progress bar for my taskbar which tells me the percentage of my day so far I've spent on work. It also includes the timetoday script, which, if you put the executable in your PATH, allows you to see how you've been dividing your time between the window tags.
In order for the blue work-time bar to work, as well as the below steps, you must edit your rc.lua window tags list (`awful.tag({*****}, s, awful.layout.layouts[1])`), and set the first 3 tags to something work-related, and keep your work activities in those tags


To install:
1. Compile timetoday.c++ (`gcc /path/to/timetoday.cpp`) and move the resulting a.out to timetoday
2. Copy and paste the contents of the .lua file into your rc.lua, and change the `EXECPATH` to the path to your timetoday executable's path
3. Replace the code in your rc.lua between `-- View tag only` and `-- Toggle tag display` -- the key binding for switching tags -- with the following:

```
awful.key({ modkey }, "#" .. i + 9,
                  function ()
                        local screen = awful.screen.focused()
                        local tag = screen.tags[i]
                        if tag then
                           tag:view_only()
                        awful.util.spawn_with_shell("{ date; echo '" .. (i - 1) .. "'; } >> ~/bin/timelog.txt ")
                        end
                  end,
                  {description = "view tag #"..i, group = "tag"}),
```

4. If you use a laptop, save sleep.sh in your system's sleep directory and make it executable (`chmod +x /path/to/sleep.sh`), so the timetoday doesn't count the time when your computer was asleep:

