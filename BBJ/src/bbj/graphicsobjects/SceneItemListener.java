/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bbj.graphicsobjects;

import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

/**
 *
 * @author Alexander
 */
public class SceneItemListener implements MouseListener {
    
    @Override
    public void mouseClicked(MouseEvent e) {
        
        UIFreeComment c = (UIFreeComment)e.getSource();
        System.out.println(c.getText()+" pressed");  

    }

    @Override
    public void mousePressed(MouseEvent e) {
        
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        
    }

    @Override
    public void mouseExited(MouseEvent e) {
       
    }
    
}
