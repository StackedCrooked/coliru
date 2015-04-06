-- our current module
local mod = {}

-- first direction: we inherit the caller scope
setmetatable(mod, { __index = _ENV })

-- second direction: avoid polluting the caller scope
_ENV = mod
mod.exports = {}

-- privacy by default
function hidden()
    return 3
end

function exports.public()
    return hidden + 4
end

return mod.exports