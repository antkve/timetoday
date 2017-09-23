-- Add this part anywhere in your rc.lua {{{
-- Change EXECPATH to the path you put the timetoday executable into
mytimebar = awful.widget.progressbar()
mytimebar:set_border_color('#333333')
mytimebar:set_background_color('#333333')
mytimebar:set_color('#0000FF')
mytimebar:set_width(50)


mytimebartimer = timer({ timeout = 10 })

mytimebartimer:connect_signal("timeout", function()
        
        f = io.popen(EXECPATH, r)
        secs = {}
        i = 0
        for line in f:lines() do 
          
          secs[i] = string.match(line, '%l+: (%d+)')
          i = i + 1
        end

        f:close()
        
        percentWork = (tonumber(secs[0]) + tonumber(secs[1]) + tonumber(secs[2]))/28800
        
        if percentWork < 0.2 then
          mytimebar:set_color('#FF0000')
        --elseif percentWork < 0.6 then
          --mytimebar:set_color('#FFFF00')
        else
          mytimebar:set_color('#0000FF')
        end
        
        mytimebar:set_value(percentWork)
        
      end)
mytimebartimer:start()
mytimebartimer:emit_signal("timeout")






