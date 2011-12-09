/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj;

import java.awt.*;
import java.util.*;

/** @file Класс содержит разнообразные статические функции общего назначения.
 * 
 * @author Lemon
 */
public class Commons {
    public Commons(){
        
    }
    
    public static void doAnything(){
        
    }
 
    public static void tuneRendering(Graphics2D g2){
        if (BBJ.qltAntialiasing != null)
            g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, BBJ.qltAntialiasing);
        
        // Text antialiasing
        if (BBJ.qltTextAntialiasing1 != null)
            g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, BBJ.qltTextAntialiasing1);
        if (BBJ.qltTextAntialiasing2 != null)
            g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, BBJ.qltTextAntialiasing2);
        if (BBJ.qltTextAntialiasing3 != null)
            g2.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING, BBJ.qltTextAntialiasing3);
        if (BBJ.qltTextAntialiasing4 != null)
            g2.setRenderingHint(RenderingHints.KEY_FRACTIONALMETRICS, BBJ.qltTextAntialiasing4);
        
        
        if (BBJ.qltInterpolation != null)
            g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, BBJ.qltInterpolation);
        
        if (BBJ.qltRender1 != null)
            g2.setRenderingHint(RenderingHints.KEY_RENDERING, BBJ.qltRender1);  
        if (BBJ.qltRender2 != null)
            g2.setRenderingHint(RenderingHints.KEY_DITHERING, BBJ.qltRender2); 
        if (BBJ.qltRender3 != null)
            g2.setRenderingHint(RenderingHints.KEY_COLOR_RENDERING, BBJ.qltRender3); 
        
        if (BBJ.qltAlphaInterpolation != null)
            g2.setRenderingHint(RenderingHints.KEY_ALPHA_INTERPOLATION, BBJ.qltAlphaInterpolation);
    }
 
}

