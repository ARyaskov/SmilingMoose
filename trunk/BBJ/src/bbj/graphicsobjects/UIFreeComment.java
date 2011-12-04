/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Polygon;
import java.awt.geom.GeneralPath;

/**
 *
 * @author Alexander
 */
public class UIFreeComment extends  SceneItem {

    @Override
    public void draw(Graphics g) {

        Polygon p = new Polygon();
        p.addPoint(0, 0);
        p.addPoint(0, 60);
        p.addPoint(60, 60);
        p.addPoint(60, 0);
        
        g.setColor(Color.orange);
        g.fillPolygon(p);
        
        g.setColor(Color.black);
        g.drawPolygon(p);
        
        g.drawString("TESTasdasdasdasdasd", 5, 20); 
    }
    
}
