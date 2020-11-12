import { Component, OnInit, Input } from '@angular/core';
import { Exam } from 'src/app/models/exam';
import { Summary } from 'src/app/models/summary';
import { Solution } from 'src/app/models/solution';

@Component({
  selector: 'app-preview-tile',
  templateUrl: './preview-tile.component.html',
  styleUrls: ['./preview-tile.component.scss']
})
export class PreviewTileComponent implements OnInit {

  @Input()
  data: Exam | Solution | Summary;

  constructor() { }


  ngOnInit() {
  }


}
