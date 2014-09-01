    point3d get_intersection(point3d topfrontleft, point3d backbottomright, point3d source)
    {
        //find the middle
        point3d middle(topfrontleft.x/2+backbottomright.x/2,
                       topfrontleft.y/2+backbottomright.y/2,
                       topfrontleft.z/2+backbottomright.z/2);
        //slide box and source as if the "middle" was at the origin
        topfrontleft -= middle;
        backbottomright-= middle;
        source -= middle;
        //scale source as if the box is the unit square
        source /= topfrontleft;
        //scale the source so that it touches the box
        if (source.x < source.y && source.x < source.z) {
            source.y /= source.x;
            source.z /= source.x;
            source.x = 1;
        } else if (source.y < source.x && source.y < source.z) {
            source.x /= source.y;
            source.z /= source.y;
            source.y = 1;
        } else if (source.z < source.x && source.z < source.y) {
            source.x /= source.z;
            source.y /= source.z;
            source.z = 1;
        }
        //then scale and slide that touching point back to original coordinates
        source = source * topfrontleft + middle;
        return source;
    }
